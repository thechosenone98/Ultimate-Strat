/* 
 * File:   waveshare29epaper.h
 * Author: zacfi
 *
 * Created on November 27, 2020, 8:34 PM
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef WAVESHARE29EPAPER_H
#define	WAVESHARE29EPAPER_H

// Display resolution
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

// EPD2IN9 commands
#define DRIVER_OUTPUT_CONTROL                       0x01
#define BOOSTER_SOFT_START_CONTROL                  0x0C
#define GATE_SCAN_START_POSITION                    0x0F
#define DEEP_SLEEP_MODE                             0x10
#define DATA_ENTRY_MODE_SETTING                     0x11
#define SW_RESET                                    0x12
#define TEMPERATURE_SENSOR_CONTROL                  0x1A
#define MASTER_ACTIVATION                           0x20
#define DISPLAY_UPDATE_CONTROL_1                    0x21
#define DISPLAY_UPDATE_CONTROL_2                    0x22
#define WRITE_RAM                                   0x24
#define WRITE_VCOM_REGISTER                         0x2C
#define WRITE_LUT_REGISTER                          0x32
#define SET_DUMMY_LINE_PERIOD                       0x3A
#define SET_GATE_TIME                               0x3B
#define BORDER_WAVEFORM_CONTROL                     0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define TERMINATE_FRAME_READ_WRITE                  0xFF

extern const uint8_t lut_full_update[30];
extern const uint8_t lut_partial_update[30];

void InitDisplay(const uint8_t* lut);
void SendCommand(uint8_t command);
void SendData(uint8_t data);
void WaitUntilIdle(void);
void ResetDisplay(void);
void SetLut(const uint8_t* lut);
void SetFrameMemoryPartial(const uint8_t* image_buffer, uint16_t x, uint16_t y, uint16_t image_width, uint16_t image_height, bool invert_color);
void SetFrameMemoryFull(const uint8_t* image_buffer, bool invert_color);
void ClearFrameMemory(uint8_t color);
void ClearFrameMemoryPartial(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint8_t color);
void DisplayFrame(void);
void SetMemoryArea(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void SetMemoryPointer(uint16_t x, uint16_t y);
void SleepDisplay(void);

#endif	/*WAVESHARE29EPAPER_H */

