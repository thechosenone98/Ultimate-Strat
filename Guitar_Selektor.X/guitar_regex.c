/* Generated by re2c 1.0.1 on Sun Dec 20 23:28:43 2020 */
#line 1 "guitar_regex.re"
/*
 *   ____                __                        
 *  /\  _`\   __        /\ \                       
 *  \ \ \L\ \/\_\    ___\ \ \/'\   __  __  _____   
 *   \ \ ,__/\/\ \  /'___\ \ , <  /\ \/\ \/\ '__`\ 
 *    \ \ \/  \ \ \/\ \__/\ \ \\`\\ \ \_\ \ \ \L\ \
 *     \ \_\   \ \_\ \____\\ \_\ \_\ \____/\ \ ,__/
 *      \/_/    \/_/\/____/ \/_/\/_/\/___/  \ \ \/ 
 *                                           \ \_\ 
 *                                            \/_/ 
 *   ____                       ___                 
 *  /\  _`\                   /'___\ __             
 *  \ \ \/\_\    ___     ___ /\ \__//\_\     __     
 *   \ \ \/_/_  / __`\ /' _ `\ \ ,__\/\ \  /'_ `\   
 *    \ \ \L\ \/\ \L\ \/\ \/\ \ \ \_/\ \ \/\ \L\ \  
 *     \ \____/\ \____/\ \_\ \_\ \_\  \ \_\ \____ \ 
 *      \/___/  \/___/  \/_/\/_/\/_/   \/_/\/___L\ \
 *                                           /\____/
 *                                           \_/__/ 
 *   ____                              __                  
 *  /\  _`\                           /\ \                 
 *  \ \ \/\ \     __    ___    ___    \_\ \     __   _ __  
 *   \ \ \ \ \  /'__`\ /'___\ / __`\  /'_` \  /'__`\/\`'__\
 *    \ \ \_\ \/\  __//\ \__//\ \L\ \/\ \L\ \/\  __/\ \ \/ 
 *     \ \____/\ \____\ \____\ \____/\ \___,_\ \____\\ \_\ 
 *      \/___/  \/____/\/____/\/___/  \/__,_ /\/____/ \/_/ 
 *                                                         
 *                                                         
 *  
 *          Zacharie McCormick <zacharie.mccormick@uqtr.ca>
 *  
 *  =======================================================
 *  
 *  Copyright (C) [yyyy] [name of copyright owner]
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  
 *  =======================================================
 *  
 */

 // This code is useful if you plan on receiving the pickup configuration trough a UART port as text (mostly during test phases)

#include <xc.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "guitar_regex.h"

const char possible_pickup_conf_str[17][10] = {"X",
                                     "N",
                                     "S",
                                     "N'",
                                     "S'",
                                     "N+S",
                                     "S+N",
                                     "N+S'",
                                     "S'+N",
                                     "N'+S",
                                     "S+N'",
                                     "N'+S'",
                                     "S'+N'",
                                     "N//S",
                                     "N'//S",
                                     "N//S'",
                                     "N'//S'"};

const char possible_general_conf_str[23][10] = {"N",
                                            "M",
                                            "B",
                                            "N+M",
                                            "M+N",
                                            "N+B",
                                            "B+N",
                                            "M+B",
                                            "B+M",
                                            "N+M+B",
                                            "N+B+M",
                                            "B+N+M",
                                            "B+M+N",
                                            "N//M",
                                            "N//B",
                                            "M//B",
                                            "N//M//B",
                                            "N//M+B",
                                            "B+N//M",
                                            "N+M//B",
                                            "M//B+N",
                                            "N//B+M",
                                            "M+N//B"};

void strncopy(char* s, char* e, char* buffer_conf){
    uint8_t i = 0;
    for(;s < e; ++s) buffer_conf[i++] = *s;
    buffer_conf[i] = '\0';
}

uint8_t find_match(char *s,bool pick_gen){
    uint8_t index = 0;
    while(strcmp(s, pick_gen ? possible_pickup_conf_str[index++]:possible_general_conf_str[index++]));
    return index - 1;
}

void get_pickup_conf(char* YYCURSOR, PickupConfiguration* pc){
    char *YYMARKER, *o1, *o2, *o3, *o4;
    char n[10];
    char m[10];
    char b[10];
    char g[10];
    char*yyt1;char*yyt2;char*yyt3;char*yyt4;
    
    
#line 128 "guitar_regex.c"
{
	char yych;
	yych = *YYCURSOR;
	switch (yych) {
	case ' ':
		yyt1 = YYCURSOR;
		goto yy3;
	case 'N':
	case 'S':
	case 'n':
	case 's':
		yyt1 = YYCURSOR;
		goto yy4;
	case 'X':
	case 'x':
		yyt1 = YYCURSOR;
		goto yy5;
	default:	goto yy2;
	}
yy2:
	YYCURSOR = YYMARKER;
	goto yy14;
yy3:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':
		yyt2 = YYCURSOR;
		goto yy6;
	case 'N':
	case 'S':
	case 'n':
	case 's':
		yyt2 = YYCURSOR;
		goto yy7;
	case 'X':
	case 'x':
		yyt2 = YYCURSOR;
		goto yy8;
	default:	goto yy2;
	}
yy4:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	case '\'':	goto yy9;
	case '+':	goto yy10;
	case '/':	goto yy11;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy12;
	case 'X':
	case 'x':	goto yy5;
	default:	goto yy2;
	}
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	default:	goto yy2;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':
		yyt3 = YYCURSOR;
		goto yy13;
	case 'N':
	case 'S':
	case 'n':
	case 's':
		yyt3 = YYCURSOR;
		goto yy15;
	case 'X':
	case 'x':
		yyt3 = YYCURSOR;
		goto yy16;
	default:	goto yy2;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	case '\'':	goto yy17;
	case '+':	goto yy18;
	case '/':	goto yy19;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy20;
	case 'X':
	case 'x':	goto yy8;
	default:	goto yy2;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	default:	goto yy2;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	case '+':	goto yy10;
	case '/':	goto yy11;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy12;
	case 'X':
	case 'x':	goto yy5;
	default:	goto yy2;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy12;
	case 'X':
	case 'x':	goto yy5;
	default:	goto yy2;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy10;
	default:	goto yy2;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	case '\'':	goto yy21;
	case 'X':
	case 'x':	goto yy5;
	default:	goto yy2;
	}
yy13:
	yych = *++YYCURSOR;
	yyt4 = YYCURSOR;
	switch (yych) {
	case 'B':
	case 'M':
	case 'N':
	case 'b':
	case 'm':
	case 'n':	goto yy22;
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
yy14:
	o1 = yyt1;
	o2 = yyt2;
	o3 = yyt3;
	o4 = yyt4;
#line 134 "guitar_regex.re"
	{
        strncopy(o1, o2 - 1, n);
        strncopy(o2, o3 - 1, m);
        strncopy(o3, o4 - 1, b);
        strncopy(o4, YYCURSOR, g);
		printf("N: %s M: %s B: %s G: %s\n", n, m, b, g);
        pc->neck = find_match(n,1);
        pc->middle = find_match(m,1);
        pc->bridge = find_match(b,1);
        pc->general = find_match(g,0);
        return;
    }
#line 302 "guitar_regex.c"
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	case '\'':	goto yy24;
	case '+':	goto yy25;
	case '/':	goto yy26;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy27;
	case 'X':
	case 'x':	goto yy16;
	default:	goto yy2;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	default:	goto yy2;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	case '+':	goto yy18;
	case '/':	goto yy19;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy20;
	case 'X':
	case 'x':	goto yy8;
	default:	goto yy2;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy20;
	case 'X':
	case 'x':	goto yy8;
	default:	goto yy2;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy18;
	default:	goto yy2;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	case '\'':	goto yy28;
	case 'X':
	case 'x':	goto yy8;
	default:	goto yy2;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy3;
	case 'X':
	case 'x':	goto yy5;
	default:	goto yy2;
	}
yy22:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '+':	goto yy29;
	case '/':	goto yy30;
	case 'B':
	case 'M':
	case 'N':
	case 'b':
	case 'm':
	case 'n':	goto yy31;
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
yy23:
	++YYCURSOR;
	goto yy14;
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	case '+':	goto yy25;
	case '/':	goto yy26;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy27;
	case 'X':
	case 'x':	goto yy16;
	default:	goto yy2;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	case 'N':
	case 'S':
	case 'n':
	case 's':	goto yy27;
	case 'X':
	case 'x':	goto yy16;
	default:	goto yy2;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy25;
	default:	goto yy2;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	case '\'':	goto yy32;
	case 'X':
	case 'x':	goto yy16;
	default:	goto yy2;
	}
yy28:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy6;
	case 'X':
	case 'x':	goto yy8;
	default:	goto yy2;
	}
yy29:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '+':	goto yy33;
	case '/':	goto yy34;
	case 'B':
	case 'M':
	case 'N':
	case 'b':
	case 'm':
	case 'n':	goto yy31;
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy29;
	default:	goto yy2;
	}
yy31:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '+':	goto yy33;
	case '/':	goto yy34;
	case 'B':
	case 'M':
	case 'N':
	case 'b':
	case 'm':
	case 'n':	goto yy35;
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
	case ' ':	goto yy13;
	case 'X':
	case 'x':	goto yy16;
	default:	goto yy2;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'B':
	case 'M':
	case 'N':
	case 'b':
	case 'm':
	case 'n':	goto yy35;
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
	case '/':	goto yy33;
	default:	goto yy2;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'X':
	case 'x':	goto yy23;
	default:	goto yy14;
	}
}
#line 146 "guitar_regex.re"

}

int main_test(int argc, char const *argv[])
{
	PickupConfiguration pc;
	get_pickup_conf("N'+S N N N+M+B", &pc);
	printf("N:%d	M:%d	B:%d	G:%d\n",pc.neck, pc.middle, pc.bridge, pc.general);
	return 0;
}