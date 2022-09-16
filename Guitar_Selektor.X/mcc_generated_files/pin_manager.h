/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF1769
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set PUSH_BTN aliases
#define PUSH_BTN_TRIS                 TRISAbits.TRISA0
#define PUSH_BTN_LAT                  LATAbits.LATA0
#define PUSH_BTN_PORT                 PORTAbits.RA0
#define PUSH_BTN_WPU                  WPUAbits.WPUA0
#define PUSH_BTN_OD                   ODCONAbits.ODA0
#define PUSH_BTN_ANS                  ANSELAbits.ANSA0
#define PUSH_BTN_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PUSH_BTN_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PUSH_BTN_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PUSH_BTN_GetValue()           PORTAbits.RA0
#define PUSH_BTN_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PUSH_BTN_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PUSH_BTN_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define PUSH_BTN_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define PUSH_BTN_SetPushPull()        do { ODCONAbits.ODA0 = 0; } while(0)
#define PUSH_BTN_SetOpenDrain()       do { ODCONAbits.ODA0 = 1; } while(0)
#define PUSH_BTN_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define PUSH_BTN_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set SHTDN aliases
#define SHTDN_TRIS                 TRISAbits.TRISA1
#define SHTDN_LAT                  LATAbits.LATA1
#define SHTDN_PORT                 PORTAbits.RA1
#define SHTDN_WPU                  WPUAbits.WPUA1
#define SHTDN_OD                   ODCONAbits.ODA1
#define SHTDN_ANS                  ANSELAbits.ANSA1
#define SHTDN_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SHTDN_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SHTDN_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SHTDN_GetValue()           PORTAbits.RA1
#define SHTDN_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SHTDN_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SHTDN_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define SHTDN_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define SHTDN_SetPushPull()        do { ODCONAbits.ODA1 = 0; } while(0)
#define SHTDN_SetOpenDrain()       do { ODCONAbits.ODA1 = 1; } while(0)
#define SHTDN_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SHTDN_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set COIL_RST aliases
#define COIL_RST_TRIS                 TRISAbits.TRISA2
#define COIL_RST_LAT                  LATAbits.LATA2
#define COIL_RST_PORT                 PORTAbits.RA2
#define COIL_RST_WPU                  WPUAbits.WPUA2
#define COIL_RST_OD                   ODCONAbits.ODA2
#define COIL_RST_ANS                  ANSELAbits.ANSA2
#define COIL_RST_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define COIL_RST_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define COIL_RST_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define COIL_RST_GetValue()           PORTAbits.RA2
#define COIL_RST_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define COIL_RST_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define COIL_RST_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define COIL_RST_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define COIL_RST_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define COIL_RST_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define COIL_RST_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define COIL_RST_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set DATA_CMD aliases
#define DATA_CMD_TRIS                 TRISAbits.TRISA4
#define DATA_CMD_LAT                  LATAbits.LATA4
#define DATA_CMD_PORT                 PORTAbits.RA4
#define DATA_CMD_WPU                  WPUAbits.WPUA4
#define DATA_CMD_OD                   ODCONAbits.ODA4
#define DATA_CMD_ANS                  ANSELAbits.ANSA4
#define DATA_CMD_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define DATA_CMD_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define DATA_CMD_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define DATA_CMD_GetValue()           PORTAbits.RA4
#define DATA_CMD_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define DATA_CMD_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define DATA_CMD_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define DATA_CMD_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define DATA_CMD_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define DATA_CMD_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define DATA_CMD_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define DATA_CMD_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set COIL_SEL aliases
#define COIL_SEL_TRIS                 TRISAbits.TRISA5
#define COIL_SEL_LAT                  LATAbits.LATA5
#define COIL_SEL_PORT                 PORTAbits.RA5
#define COIL_SEL_WPU                  WPUAbits.WPUA5
#define COIL_SEL_OD                   ODCONAbits.ODA5
#define COIL_SEL_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define COIL_SEL_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define COIL_SEL_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define COIL_SEL_GetValue()           PORTAbits.RA5
#define COIL_SEL_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define COIL_SEL_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define COIL_SEL_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define COIL_SEL_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define COIL_SEL_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define COIL_SEL_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set ROT_A aliases
#define ROT_A_TRIS                 TRISBbits.TRISB4
#define ROT_A_LAT                  LATBbits.LATB4
#define ROT_A_PORT                 PORTBbits.RB4
#define ROT_A_WPU                  WPUBbits.WPUB4
#define ROT_A_OD                   ODCONBbits.ODB4
#define ROT_A_ANS                  ANSELBbits.ANSB4
#define ROT_A_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define ROT_A_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define ROT_A_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define ROT_A_GetValue()           PORTBbits.RB4
#define ROT_A_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define ROT_A_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define ROT_A_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define ROT_A_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define ROT_A_SetPushPull()        do { ODCONBbits.ODB4 = 0; } while(0)
#define ROT_A_SetOpenDrain()       do { ODCONBbits.ODB4 = 1; } while(0)
#define ROT_A_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define ROT_A_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set ROT_B aliases
#define ROT_B_TRIS                 TRISBbits.TRISB5
#define ROT_B_LAT                  LATBbits.LATB5
#define ROT_B_PORT                 PORTBbits.RB5
#define ROT_B_WPU                  WPUBbits.WPUB5
#define ROT_B_OD                   ODCONBbits.ODB5
#define ROT_B_ANS                  ANSELBbits.ANSB5
#define ROT_B_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define ROT_B_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define ROT_B_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define ROT_B_GetValue()           PORTBbits.RB5
#define ROT_B_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define ROT_B_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define ROT_B_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define ROT_B_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define ROT_B_SetPushPull()        do { ODCONBbits.ODB5 = 0; } while(0)
#define ROT_B_SetOpenDrain()       do { ODCONBbits.ODB5 = 1; } while(0)
#define ROT_B_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define ROT_B_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set A1 aliases
#define A1_TRIS                 TRISCbits.TRISC0
#define A1_LAT                  LATCbits.LATC0
#define A1_PORT                 PORTCbits.RC0
#define A1_WPU                  WPUCbits.WPUC0
#define A1_OD                   ODCONCbits.ODC0
#define A1_ANS                  ANSELCbits.ANSC0
#define A1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define A1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define A1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define A1_GetValue()           PORTCbits.RC0
#define A1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define A1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define A1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define A1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define A1_SetPushPull()        do { ODCONCbits.ODC0 = 0; } while(0)
#define A1_SetOpenDrain()       do { ODCONCbits.ODC0 = 1; } while(0)
#define A1_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define A1_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set A2 aliases
#define A2_TRIS                 TRISCbits.TRISC1
#define A2_LAT                  LATCbits.LATC1
#define A2_PORT                 PORTCbits.RC1
#define A2_WPU                  WPUCbits.WPUC1
#define A2_OD                   ODCONCbits.ODC1
#define A2_ANS                  ANSELCbits.ANSC1
#define A2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define A2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define A2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define A2_GetValue()           PORTCbits.RC1
#define A2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define A2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define A2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define A2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define A2_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define A2_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define A2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define A2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set A3 aliases
#define A3_TRIS                 TRISCbits.TRISC2
#define A3_LAT                  LATCbits.LATC2
#define A3_PORT                 PORTCbits.RC2
#define A3_WPU                  WPUCbits.WPUC2
#define A3_OD                   ODCONCbits.ODC2
#define A3_ANS                  ANSELCbits.ANSC2
#define A3_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define A3_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define A3_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define A3_GetValue()           PORTCbits.RC2
#define A3_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define A3_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define A3_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define A3_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define A3_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define A3_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define A3_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define A3_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set BUSY aliases
#define BUSY_TRIS                 TRISCbits.TRISC3
#define BUSY_LAT                  LATCbits.LATC3
#define BUSY_PORT                 PORTCbits.RC3
#define BUSY_WPU                  WPUCbits.WPUC3
#define BUSY_OD                   ODCONCbits.ODC3
#define BUSY_ANS                  ANSELCbits.ANSC3
#define BUSY_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define BUSY_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define BUSY_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define BUSY_GetValue()           PORTCbits.RC3
#define BUSY_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define BUSY_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define BUSY_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define BUSY_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define BUSY_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define BUSY_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define BUSY_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define BUSY_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set EINK_SEL aliases
#define EINK_SEL_TRIS                 TRISCbits.TRISC4
#define EINK_SEL_LAT                  LATCbits.LATC4
#define EINK_SEL_PORT                 PORTCbits.RC4
#define EINK_SEL_WPU                  WPUCbits.WPUC4
#define EINK_SEL_OD                   ODCONCbits.ODC4
#define EINK_SEL_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define EINK_SEL_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define EINK_SEL_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define EINK_SEL_GetValue()           PORTCbits.RC4
#define EINK_SEL_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define EINK_SEL_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define EINK_SEL_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define EINK_SEL_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define EINK_SEL_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define EINK_SEL_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)

// get/set EINK_RST aliases
#define EINK_RST_TRIS                 TRISCbits.TRISC5
#define EINK_RST_LAT                  LATCbits.LATC5
#define EINK_RST_PORT                 PORTCbits.RC5
#define EINK_RST_WPU                  WPUCbits.WPUC5
#define EINK_RST_OD                   ODCONCbits.ODC5
#define EINK_RST_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define EINK_RST_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define EINK_RST_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define EINK_RST_GetValue()           PORTCbits.RC5
#define EINK_RST_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define EINK_RST_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define EINK_RST_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define EINK_RST_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define EINK_RST_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define EINK_RST_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

// get/set COIL_DATA aliases
#define COIL_DATA_TRIS                 TRISCbits.TRISC6
#define COIL_DATA_LAT                  LATCbits.LATC6
#define COIL_DATA_PORT                 PORTCbits.RC6
#define COIL_DATA_WPU                  WPUCbits.WPUC6
#define COIL_DATA_OD                   ODCONCbits.ODC6
#define COIL_DATA_ANS                  ANSELCbits.ANSC6
#define COIL_DATA_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define COIL_DATA_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define COIL_DATA_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define COIL_DATA_GetValue()           PORTCbits.RC6
#define COIL_DATA_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define COIL_DATA_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define COIL_DATA_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define COIL_DATA_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define COIL_DATA_SetPushPull()        do { ODCONCbits.ODC6 = 0; } while(0)
#define COIL_DATA_SetOpenDrain()       do { ODCONCbits.ODC6 = 1; } while(0)
#define COIL_DATA_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define COIL_DATA_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set COIL_CLK aliases
#define COIL_CLK_TRIS                 TRISCbits.TRISC7
#define COIL_CLK_LAT                  LATCbits.LATC7
#define COIL_CLK_PORT                 PORTCbits.RC7
#define COIL_CLK_WPU                  WPUCbits.WPUC7
#define COIL_CLK_OD                   ODCONCbits.ODC7
#define COIL_CLK_ANS                  ANSELCbits.ANSC7
#define COIL_CLK_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define COIL_CLK_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define COIL_CLK_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define COIL_CLK_GetValue()           PORTCbits.RC7
#define COIL_CLK_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define COIL_CLK_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define COIL_CLK_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define COIL_CLK_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define COIL_CLK_SetPushPull()        do { ODCONCbits.ODC7 = 0; } while(0)
#define COIL_CLK_SetOpenDrain()       do { ODCONCbits.ODC7 = 1; } while(0)
#define COIL_CLK_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define COIL_CLK_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF0 pin functionality
 * @Example
    IOCAF0_ISR();
 */
void IOCAF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_InterruptHandler);

*/
extern void (*IOCAF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_DefaultInterruptHandler);

*/
void IOCAF0_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/