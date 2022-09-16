/*
 * File:   waveshare29epaper.c
 * Author: zacfi
 *
 * Created on November 27, 2020, 8:33 PM
 */


#include <xc.h>
#include "waveshare29epaper.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/spi.h"
#include "mcc_generated_files/delay.h"
// <editor-fold defaultstate="collapsed" desc="GLOBAL VARIABLES">
uint8_t partial_refresh_count = 0;
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="LUT">
const uint8_t lut_full_update[] = {
    0x50, 0xAA, 0x55, 0xAA, 0x11, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t lut_partial_update[] = {
    0x10, 0x18, 0x18, 0x08, 0x18, 0x18,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x13, 0x14, 0x44, 0x12,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="E-Paper Functions">
void InitDisplay(const uint8_t* lut){
    ResetDisplay();
    SendCommand(DRIVER_OUTPUT_CONTROL);
    SendData((EPD_HEIGHT - 1) & 0xFF);
    SendData(((EPD_HEIGHT - 1) >> 8) & 0xFF);
    SendData(0x00);                     // GD = 0; SM = 0; TB = 0;
    SendCommand(BOOSTER_SOFT_START_CONTROL);
    SendData(0xD7);
    SendData(0xD6);
    SendData(0x9D);
    SendCommand(WRITE_VCOM_REGISTER);
    SendData(0xA8);                     // VCOM 7C
    SendCommand(SET_DUMMY_LINE_PERIOD);
    SendData(0x1A);                     // 4 dummy lines per gate
    SendCommand(SET_GATE_TIME);
    SendData(0x08);                     // 2us per line
    SendCommand(DATA_ENTRY_MODE_SETTING);
    SendData(0x03);                     // X increment; Y increment
    SetLut(lut);
}

/**
 *  @brief: basic function for sending commands
 */
void SendCommand(uint8_t command){
    EINK_SEL_SetLow();
    DATA_CMD_SetLow();
    SPI_ExchangeByte(command);
    EINK_SEL_SetHigh();
}

/**
 *  @brief: basic function for sending data
 */
void SendData(uint8_t data){
    EINK_SEL_SetLow();
    DATA_CMD_SetHigh();
    SPI_ExchangeByte(data);
    EINK_SEL_SetHigh();
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void WaitUntilIdle(void){
    while (BUSY_GetValue() == 1) {
        DELAY_milliseconds(10);
    }
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void ResetDisplay(void){
    EINK_RST_SetLow();
    DELAY_milliseconds(200);
    EINK_RST_SetHigh();
    DELAY_milliseconds(200);
}

/**
 *  @brief: set the look-up table register
 */
void SetLut(const uint8_t* lut){
    SendCommand(WRITE_LUT_REGISTER);
    int i;
    for (i = 0; i < 30; i++)
        SendData(lut[i]);
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void SetFrameMemoryPartial(const uint8_t* image_buffer, uint16_t x, uint16_t y, uint16_t image_width, uint16_t image_height, bool invert_color){
    uint16_t x_end, y_end;
    
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    x &= 0xF8;
    image_width &= 0xF8;
    if (x + image_width >= EPD_WIDTH) {
        x_end = EPD_WIDTH - 1;
    } else {
        x_end = x + image_width - 1;
    }
    if (y + image_height >= EPD_HEIGHT) {
        y_end = EPD_HEIGHT - 1;
    } else {
        y_end = y + image_height - 1;
    }
    SetMemoryArea(x, y, x_end, y_end);
    SetMemoryPointer(x, y);
    SendCommand(WRITE_RAM);
    /* send the image data */
    uint8_t data;
    uint16_t i, j;
    for (j = 0; j < y_end - y + 1; j++) {
        for (i = 0; i < (x_end - x + 1) / 8; i++) {
            data = image_buffer[i + j * (image_width / 8)];
            SendData(invert_color ? ~data : data);
        }
    }
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 *          This version of the function sets sets the whole memory area.
 *          It of course needs an image buffer of the size of the whole screen to do so.
 */
void SetFrameMemoryFull(const uint8_t* image_buffer, bool invert_color) {
    SetMemoryArea(0, 0, EPD_WIDTH - 1, EPD_HEIGHT - 1);
    SetMemoryPointer(0, 0);
    SendCommand(WRITE_RAM);
    /* send the image data */
    uint8_t data;
    uint16_t i;
    for (i = 0; i < EPD_WIDTH / 8 * EPD_HEIGHT; i++) {
        data = image_buffer[i];
        SendData(invert_color ? ~data : data);
    }
}

/**
 *  @brief: clear the frame memory with the specified color.
 *          this won't update the display.
 */
void ClearFrameMemory(uint8_t color) {
    SetMemoryArea(0, 0, EPD_WIDTH - 1, EPD_HEIGHT - 1);
    SetMemoryPointer(0, 0);
    SendCommand(WRITE_RAM);
    /* send the color data */
    uint16_t i;
    for (i = 0; i < EPD_WIDTH / 8 * EPD_HEIGHT; i++) {
        SendData(color);
    }
}

void ClearFrameMemoryPartial(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint8_t color) {
    SetMemoryArea(x_start, y_start, x_end, y_end);
    SetMemoryPointer(x_start, y_start);
    SendCommand(WRITE_RAM);
    /* send the color data */
    uint16_t i;
    for (i = 0; i < (x_end - x_start) * (y_end - y_start); i++) {
        SendData(color);
    }
}

/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will 
 *          set the other memory area.
 */
void DisplayFrame(void) {
    //FOR TESTING
    partial_refresh_count++;
    if(partial_refresh_count >= 6)
    {
        InitDisplay(lut_full_update);
        partial_refresh_count = 0;
        SendCommand(DISPLAY_UPDATE_CONTROL_2);
        SendData(0xC4);
        SendCommand(MASTER_ACTIVATION);
        SendCommand(TERMINATE_FRAME_READ_WRITE);
        WaitUntilIdle();
        InitDisplay(lut_partial_update);
    } 
    else
    {
        SendCommand(DISPLAY_UPDATE_CONTROL_2);
        SendData(0xC4);
        SendCommand(MASTER_ACTIVATION);
        SendCommand(TERMINATE_FRAME_READ_WRITE);
        WaitUntilIdle();
    }
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */
void SetMemoryArea(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {
    SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x_start >> 3) & 0xFF);
    SendData((x_end >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
    SendData(y_start & 0xFF);
    SendData((y_start >> 8) & 0xFF);
    SendData(y_end & 0xFF);
    SendData((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void SetMemoryPointer(uint16_t x, uint16_t y) {
    SendCommand(SET_RAM_X_ADDRESS_COUNTER);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    SendData((x >> 3) & 0xFF);
    SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
    SendData(y & 0xFF);
    SendData((y >> 8) & 0xFF);
    WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the 
 *          deep-sleep mode to save power. 
 *          The deep sleep mode would return to standby by hardware reset. 
 *          You can use Epd::Init() to awaken
 */
void SleepDisplay(void) {
    SendCommand(DEEP_SLEEP_MODE);
    WaitUntilIdle();
}
// </editor-fold>