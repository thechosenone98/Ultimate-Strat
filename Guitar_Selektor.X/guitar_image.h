/* 
 * File:   guitar_image.h
 * Author: zacharie
 *
 * Created on December 19, 2020, 4:54 PM
 */

#include "guitar_regex.h"

#ifndef GUITAR_IMAGE_H
#define	GUITAR_IMAGE_H

typedef struct PickupConfigurationImage{
    uint8_t length;
    const uint8_t* image_pointers[3];
}PickupConfigurationImage;

typedef struct GeneralPickupConfigurationImage{
    uint8_t length;
    const uint8_t* image_pointers[5];
}GeneralPickupConfigurationImage;

extern const uint16_t pickup_configuration_selectors[17];
extern const uint16_t general_pickup_configuration_selectors[23];

/*Create a 296*128 image for an EPaper display from a PickupConfiguration struct*/
void ImageFromPickupConf(PickupConfiguration* pc, int8_t selection_index, bool bracket, bool draw_empty);

#endif	/* GUITAR_IMAGE_H */

