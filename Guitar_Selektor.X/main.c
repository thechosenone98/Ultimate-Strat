/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF1769
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdint.h>
#include <stdbool.h>
#include "waveshare29epaper.h"
#include "guitar_image.h"
#include "guitar_regex.h"
#include "images.h"
#include "HEFlash.h"

#define LSBFIRST 0
#define MSBFIRST 1

const uint8_t configurations[] __at(0x1f80) = {0x01,0x00,0x00,0x00,0x01,0x01,0x00,0x0E,0x00,0x01,0x00,0x01,0x00,0x01,0x01,0x0F,0x00,0x00,0x01,0x02};

//Global variable used to keep the state we are in
PickupConfiguration saved_pc[5] = { {.neck=1, .middle=2, .bridge=3, .general=4},
                                    {.neck=5, .middle=10, .bridge=4, .general=2},
                                    {.neck=2, .middle=12, .bridge=13, .general=12},
                                    {.neck=1, .middle=15, .bridge=12, .general=21},
                                    {.neck=4, .middle=1, .bridge=5, .general=17}
                                    };

int8_t selection_index = -1;
uint8_t switch_pos = 0;
uint8_t prev_switch_pos = 0;
int8_t click_type = 0; //0 -> Nothing happened, 1-> Button Clicked, 2 -> Button pressed for 1 sec, 3 -> Button pressed for 3 sec
volatile int16_t click_timer = 0;
volatile bool button_clicked = false;
volatile bool time_to_refresh = true;
volatile uint16_t refresh_timer = 0;
uint64_t coil_conf;

void sendCoilsConfiguration(PickupConfiguration *pc);
void ButtonEventReset(void);

void ReadConfigurationsFromMemory(){
    HEFLASH_readBlock((void*)&saved_pc, 0, sizeof(saved_pc));
}

void WriteConfigurationToMemory(){
    HEFLASH_writeBlock(0, (void*)&saved_pc, sizeof(saved_pc));
}

bool sleeping = false;
bool wake_up = false;
void GotoSleep(void){
    InitDisplay(lut_full_update);
    ClearFrameMemory(0xA5);
    DisplayFrame();
    SleepDisplay();
    SHTDN_SetLow();
    COIL_RST_SetLow();
    DATA_CMD_SetLow();
    COIL_SEL_SetLow();
    EINK_SEL_SetLow();
    EINK_RST_SetLow();
    COIL_DATA_SetLow();
    COIL_CLK_SetLow();
    DELAY_milliseconds(2000);
    ButtonEventReset();
    sleeping = true;
    SLEEP();
}

void WakeUp(void){
    selection_index = -1;
    SHTDN_SetHigh();
    ButtonEventReset();
    TMR1_StartTimer();
    InitDisplay(lut_full_update);
    DELAY_milliseconds(1000);
    ClearFrameMemory(0xFF);
    DisplayFrame();
    ClearFrameMemory(0xFF);
    DisplayFrame();
    ReadConfigurationsFromMemory();
//    ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
//    DisplayFrame();
//    ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
//    DisplayFrame();
    InitDisplay(lut_partial_update);
    //TODO : Remove this and treat in while loop
    sendCoilsConfiguration(&saved_pc[switch_pos]);
}

int8_t modulo(int8_t x,int8_t N){
    return (x % N + N) % N;
}

void ButtonEventReset(void){
    click_type = 0;
    click_timer = 0;
    button_clicked = 0;
}

//Timer interrupt handler for the button events
void TMR1_CallBack()
{
    if(button_clicked) ++click_timer;
    if(switch_pos != prev_switch_pos){
        if(refresh_timer++ >= 1000) time_to_refresh = true;
    }
}

//Button interrupt handler (triggered when the button is pressed)
void Button_Callback(){
    if (PUSH_BTN_GetValue() == 0){
        if(sleeping){
            sleeping = false;
            wake_up = true;
        } else {
            button_clicked = true;
        }
    }
}

//Determines the type of button click the user inputed
void ButtonCaseHandler(void){
    //printf("%d\n", click_timer); //Prints the click timer value to UART
    if(button_clicked && click_type == 0){
        if(PUSH_BTN_GetValue() == 1){
            if(click_timer < 50) ButtonEventReset();
            else if(click_timer >= 50 && click_timer < 999) click_type = 1;
            else if(click_timer >= 1000 && click_timer < 2999) click_type = 2;
            else if(click_timer >= 3000) click_type = 3;
        }
        else if(click_timer >= 5000) click_type = 4;
    }
}

//Runs different routines based on the type of the button click
void ButtonEventHandler(void){
    switch(click_type){
        case 1:
            if(selection_index >= 0){ // Must be in select mode to use single click
                //printf("Button Clicked\n");
                //Remove the bracket from the previous line and copy the image on both buffer so it does not change when we refresh the next line
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
                DisplayFrame();
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
                DisplayFrame();
                selection_index = (selection_index + 1) % 4;
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, true, false);
                DisplayFrame();
                //printf("Mode : %c\n", selection_index == 0 ? 'N' : selection_index == 1 ? 'M' : selection_index == 2 ? 'B' : 'G');
            }
            break;
        case 2:
            //printf("Button clicked for 1 sec\n");
            selection_index = selection_index == -1 ? 0 : -1; //Toggle from idle mode to select mode
            if(selection_index == -1){
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
                DisplayFrame();
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, false, false);
                DisplayFrame();
            } else {
                ImageFromPickupConf(&saved_pc[switch_pos], -1, false, true);
                DisplayFrame();
                ImageFromPickupConf(&saved_pc[switch_pos], -1, false, true);
                DisplayFrame();
                ImageFromPickupConf(&saved_pc[switch_pos], selection_index, true, false);
                DisplayFrame();
            }
            break;
        case 3:
            WriteConfigurationToMemory();
            break;
        case 4:
            //printf("Button Clicked for 3 sec\n");
            //Turn off everything
            GotoSleep();
            break;
        default:
            return;
    }
    ButtonEventReset(); //Reset the button click timer and type after the click has been handled
}

void SwitchEventHandler(void){
    //Convert gray code of switch to binary
    const uint8_t conv_table[6] = {0, 2, 1, 4, 0, 3};
    bool a1 = !A1_GetValue();
    bool a2 = !A2_GetValue();
    bool a3 = !A3_GetValue();
    //b3 is simply a3 so no point in creating a variable for it
    uint8_t new_switch_pos = conv_table[((a3 << 2) | (a2 << 1) | a1) - 1];
    if(new_switch_pos != switch_pos){
        switch_pos = new_switch_pos;
        sendCoilsConfiguration(&saved_pc[switch_pos]);
    }
}

void DisplayRefreshHandler(void){
    //Updates the display every second if need be (if the switch moved)
    //Allows fast response to switch for pickup configuration (having this runs every X ms instead
    //of every time switch changes position stops the image change from taking precedence over pickup configuration)
    if(time_to_refresh){
        prev_switch_pos = switch_pos;
        time_to_refresh = false;
        refresh_timer = 0;
        ImageFromPickupConf(&saved_pc[switch_pos], selection_index, true, false);
        DisplayFrame();
    }
}

int8_t read_rotary(void) {
    static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
    static uint8_t prevNextCode = 0;
    static uint16_t store=0;

    prevNextCode <<= 2;
    if (ROT_B_GetValue()) prevNextCode |= 0x02;
    if (ROT_A_GetValue()) prevNextCode |= 0x01;
    prevNextCode &= 0x0f;

    // If valid then store as 16 bit data.
    if  (rot_enc_table[prevNextCode] ) {
        store <<= 4;
        store |= prevNextCode;
        //if (store==0xd42b) return 1;
        //if (store==0xe817) return -1;
        if ((store&0xff)==0x2b) return -1;
        if ((store&0xff)==0x17) return 1;
    }
    return 0;
}

void RotaryEncoderEventHandler(void){
    static int8_t val;
    if(selection_index >= 0){ //If we are in select mode
        if((val = read_rotary())){
            switch(selection_index){
                case 0:
                    saved_pc[switch_pos].neck = modulo(saved_pc[switch_pos].neck + val, 17);
                    //printf("N : %s    %d\n", possible_pickup_conf_str[pc->neck], pc->neck);
                    break;
                case 1:
                    saved_pc[switch_pos].middle = modulo(saved_pc[switch_pos].middle + val, 17);
                    //printf("M : %s\n", possible_pickup_conf_str[pc->middle]);
                    break;
                case 2:
                    saved_pc[switch_pos].bridge = modulo(saved_pc[switch_pos].bridge + val, 17);
                    //printf("B : %s\n", possible_pickup_conf_str[pc->bridge]);
                    break;
                case 3:
                    saved_pc[switch_pos].general = modulo(saved_pc[switch_pos].general + val, 23);
                    //printf("G : %s\n", possible_general_conf_str[pc->general]);
                default:
                    break;
            }
            sendCoilsConfiguration(&saved_pc[switch_pos]);
            ImageFromPickupConf(&saved_pc[switch_pos], selection_index, true, false);
            DisplayFrame();
        }
    }
}

void shiftOut(uint8_t bitOrder, uint64_t val)
{
    uint64_t i;
    COIL_SEL_SetLow();
    for (i = 0; i < 48; i++)  {
        if (bitOrder == LSBFIRST)
            if (!!(val & ((uint64_t)1 << i)))
                COIL_DATA_SetHigh();
            else
                COIL_DATA_SetLow();
        else
            if (!!(val & ((uint64_t)1 << (47 - i))))
                COIL_DATA_SetHigh();
            else
                COIL_DATA_SetLow();

        COIL_CLK_SetHigh();
        COIL_CLK_SetLow();     
    }
    COIL_SEL_SetHigh();
}

void sendCoilsConfiguration(PickupConfiguration *pc){
    //Reset the coil_conf (we only OR on it so it would fill up otherwise)
    coil_conf = 0;
    //Start by filling 48 bit in the coil_conf to represent the 6x8 SPST ICs state
    coil_conf |= general_pickup_configuration_selectors[pc->general];
    coil_conf |= ((uint64_t)pickup_configuration_selectors[pc->bridge]) << 12;
    coil_conf |= ((uint64_t)pickup_configuration_selectors[pc->middle]) << 24;
    coil_conf |= ((uint64_t)pickup_configuration_selectors[pc->neck]) << 36;
    shiftOut(LSBFIRST, coil_conf);
}

/*
                         Main application
 */
int main(void)
{
    //Check for cause of RESET (if a reset occured)
    uint8_t reset_type = 0;
    if(STKOVF | STKUNF)
        reset_type = 1;
    else if(!PCONbits.nRI)
        reset_type = 2;
    else if((STATUS & 0x18) == 0x18 && (PCON & 0x0C) == 0x0C)
        reset_type = 3;
    // initialize the device
    SYSTEM_Initialize();
    //Pin setup
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR1_SetInterruptHandler(TMR1_CallBack);
    IOCAF0_SetInterruptHandler(Button_Callback);
    if(!spi_master_open(EINK)){
		// Not able to open SPI, call fail() or optionally do something 
		// else waiting for the SPI to become free
		return 0;
    }
    
    WakeUp();
    
    if(reset_type == 1){
        STKOVF = 0;
        STKUNF = 0;
        PickupConfiguration stack_pc = {.neck=15, .middle=15, .bridge=15, .general=15};
        ImageFromPickupConf(&stack_pc, selection_index, true, false);
        DisplayFrame();
        DELAY_milliseconds(2000);
    }
    else if(reset_type == 2){
        PickupConfiguration reset_pc = {.neck=16, .middle=16, .bridge=16, .general=16};
        ImageFromPickupConf(&reset_pc, selection_index, true, false);
        DisplayFrame();
        DELAY_milliseconds(2000);
    }
    else if(reset_type == 3){
        PickupConfiguration reset_pc = {.neck=8, .middle=8, .bridge=8, .general=8};
        ImageFromPickupConf(&reset_pc, selection_index, true, false);
        DisplayFrame();
        DELAY_milliseconds(2000);
    }

    while (1)
    {
        if(wake_up){
            wake_up = false;
            WakeUp();
        }
        RotaryEncoderEventHandler();
        ButtonCaseHandler();
        ButtonEventHandler();
        SwitchEventHandler();
        DisplayRefreshHandler();
    }
}
/**
 End of File
*/