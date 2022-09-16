/*
 * File:   HEFlash.c
 * Author: zacfi
 *
 * Created on May 27, 2021, 12:17 PM
 */


#include <xc.h>
#include "HEFlash.h"
/******************************************************************************
* High Endurance Flash functions
*/
char HEFLASH_writeBlock(char radd, char* buffer, char count)
{
    // 1. obtain absolute address in HE FLASH row
    unsigned add = radd * FLASH_ROWSIZE + HEFLASH_START;
    // 2. check input parameters
    if ((count > FLASH_ROWSIZE)||(radd >= HEFLASH_MAXROWS))
        return (char)-1;//return parameter error
    // 3. erase the entire row
    FLASH_erase(add);
    // 4. fill the latches with data
    while (count > 1)
    {
        //load data in latches without writing
        FLASH_write(add++, (unsigned)*buffer++, 1);
        count--;
    }
    // no delay here!!!
    // 5. last byte of data -> write
    FLASH_write (add, (unsigned) *buffer, 0);
    // NOTE: 2ms typ. delay here!!!
    // 6. return success
    return PMCON1bits.WRERR; //0 success, 1 = write error
} //HEFLASH_writeBlock
char HEFLASH_readBlock(char* buffer, char radd, char count)
{
    // 1. obtain absolute address in HE FLASH row
    unsigned add = radd * FLASH_ROWSIZE + HEFLASH_START;
    // 2. check input parameters
    if ((count > FLASH_ROWSIZE)||(radd >= HEFLASH_MAXROWS))
        return (char)-1;
    // 3. read content
    while (count > 0)
    {
        *buffer++ = (char)FLASH_read (add++);
        count--;
    }
    // 4. success
    return 0;
} //HEFLASH_readBlock
char HEFLASH_readByte(char radd, char offset)
{
    // 1. add offset into HE Flash memory
    unsigned add = radd * FLASH_ROWSIZE + HEFLASH_START + offset;
    // 2. read content
    return (char)FLASH_read (add);
} //HEFLASH_read
