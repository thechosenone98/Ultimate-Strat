/* 
 * File:   guitar_regex.h
 * Author: zacharie
 *
 * Created on December 19, 2020, 4:45 PM
 */

#ifndef GUITAR_REGEX_H
#define	GUITAR_REGEX_H

#include <stdint.h>
#include <stdbool.h>

extern const char possible_pickup_conf_str[17][10];
extern const char possible_general_conf_str[23][10];

typedef struct PickupConfiguration{
    int8_t neck;
    int8_t middle;
    int8_t bridge;
    int8_t general;
}PickupConfiguration;

void strncopy(char* s, char* e, char* buffer_conf);
uint8_t find_match(char *s,bool pick_gen);
/*
 Creates a configuration struct from a configuration string
 * that represents 3 pickup configuration and their relationship.
 * Here is a string example:
 * "N S'+N' M X B N N+B"
 * This translates to to Neck pickup being in a configuration
 * in which the south and north coils are in series and both reversed and the
 * bridge pickup only using it's north coil, the middle pickup is unused and the
 * overall pickup configuration is N in series with bridge.
 */
void get_pickup_conf(char* YYCURSOR, PickupConfiguration* pc);

#endif	/* GUITAR_REGEX_H */

