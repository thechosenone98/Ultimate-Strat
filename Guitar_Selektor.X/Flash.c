/*
 * File:   Flash.c
 * Author: zacfi
 *
 * Created on May 27, 2021, 12:14 PM
 */

#include <xc.h>
#include "Flash.h"
/******************************************************************************
* Generic Flash functions
*/
unsigned FLASH_readConfig (unsigned address)
{
    // 1. load the address pointers
    PMADR = address;
    PMCON1bits.CFGS = 1; //select the configuration Flash address space
    PMCON1bits.RD = 1; //next operation will be a read
    NOP();
    NOP();
    // 2. return value read
    return PMDAT;
}//FLASH_config
unsigned FLASH_read (unsigned address)
{
    // 1. load the address pointers
    PMADR = address;
    PMCON1bits.CFGS = 0; // select the Flash address space
    PMCON1bits.RD = 1; // next operation will be a read
    NOP();
    NOP();
    // 2. return value read
    return PMDAT;
} //FLASH_read
void FLASH_readBlock (unsigned *buffer, unsigned address, char count)
{
    while (count > 0)
    {
        *buffer++ = FLASH_read (address++);
        count--;
    }
}// FLASH_readBLock
/**
* unlock Flash Sequence
*/
void _unlock (void)
{
    __asm("BANKSEL PMCON2");
    __asm("MOVLW 0x55");
    __asm("MOVWF PMCON2 & 0x7F");
    __asm("MOVLW 0xAA");
    __asm("MOVWF PMCON2 & 0x7F");
    __asm("BSF PMCON1 & 0x7F,1 ; set WR bit");
    __asm("NOP");
    __asm("NOP");
}//unlock
void FLASH_write (unsigned address, unsigned data, char latch)
{
    // 1. disable interrupts (remember setting)
    char temp = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    // 2. load the address pointers
    PMADR = address;
    PMDAT = data;
    PMCON1bits.LWLO = latch; // 1 = latch, 0 = write row
    PMCON1bits.CFGS = 0; // select the Flash address space
    PMCON1bits.FREE = 0; // next operation will be a write
    PMCON1bits.WREN = 1; // enable Flash memory write/erase
    // 3. perform unlock sequence
    _unlock();
    // 4. restore interrupts
    if (temp)
        INTCONbits.GIE = 1;
}//FLASH_write
void FLASH_erase (unsigned address)
{
    // 1. disable interrupts (remember setting)
    char temp = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    // 2. load the address pointers
    PMADR = address;
    PMCON1bits.CFGS = 0; // select the Flash address space
    PMCON1bits.FREE = 1; // next operation will be an erase
    PMCON1bits.WREN = 1; // enable Flash memory write/erase
    // 3. perform unlock sequence and erase
    _unlock();
    // 4. disable writes and restore interrupts
    PMCON1bits.WREN = 0; // disable Flash memory write/erase
    if (temp)
        INTCONbits.GIE = 1;
}//FLASH_erase
