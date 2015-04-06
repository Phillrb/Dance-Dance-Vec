//
//  vectrex.h
//
//  Created by Martin White on 09/05/2014.
//  Copyright (c) 2014 Martin White. All rights reserved.
//
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the
//	"Software"), to deal in the Software without restriction, including
//	without limitation the rights to use, copy, modify, merge, publish,
//	distribute, sublicense, and/or sell copies of the Software, and to
//	permit persons to whom the Software is furnished to do so, subject to
//	the following conditions:
//
//	The above copyright notice and this permission notice shall be included
//	in all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

/***************************************************************
 * 
 * Include file for each Vectrex BIOS function exposed to C
 * 
 * For each method exposed in here there must also be a method
 * stub in crt0.asm that passes any parameters and handles
 * the method call / return
 * 
 ***************************************************************/

#ifndef _VECTREX_H
#define _VECTREX_H

#ifndef NULL
#define NULL 0
#endif

#include "stdbool.h"

typedef signed char		int8;
typedef unsigned char 	uint8;

// EXEC FUNCTIONS

// General functions
void reset0Ref();									// 0xF354	Reset0Ref
void waitRecal();									// 0xF192	Wait for frame buffer
void intensA(int i);								// 0xF2AB	Set beam intensity

// Delay functions
void delay0();										// 0xF579	Delay 15 cycles
void delay1();										// 0xF575	Delay 20 cycles
void delay2();										// 0xF571	Delay 25 cycles
void delay3();										// 0xF56D	Delay 30 cycles
void delayB(int cycles);							// 0xF57A	Delay given no. of cycles
void delayRTS();									// 0xF57D	Same as delay0 - for compatibility only

// Move functions
void moveToD(int x, int y);							// 0xF2FC	Move to X/Y
void moveToD7f(int x, int y);						// 0xF2FC	Move to X/Y, force scale to s7F

// Rotate functions
void rotVLMode();									// 0xF61F	Rotate VL with mode absolute
//void rotVL();											// 0xF616	Rotate VL
//void rotVLWithAngle();								// 0xF610	Rotate VL absolute
//void rotVLModeDflt(const int8 *data, int8 *newData);		// 0xF62B	Rotate VL with mode

// Draw funtions
void drawVLp(const int* data, int zskip);			// 0xF410	Draw_VLp
void drawLineD(int x, int y);						// 0xF3DF	Draw line to Y,X relative
void drawVLp7F(const int* data, int zskip);			// 0xF408	Draw_VLp_7F
void drawVLpScale(const int* data, int zskip);		// 0xF40C	Draw_VLp_Scale

// String functions
void printStrD(int y, int x, char* string);			// 0xF37A   Print 0x80 terminated string
void printStr(char *string);

// I/O functions
void joyAnalog();									// 0xF1F5	Read joystick: analog return values
void joyDigital();									// 0xF1F8	Read joystick: digital return values
//void readButtonMasked();							// 0xF1B4
void readButton();									// 0xF1BA	Read buttons and return as 1 byte mask

// Music functions
void doSound();										// 0xF289	Do Sound
void initMusicCHK(const int* data);					// 0xF687

// Score functions
void clearScore(char *score);						// 0xF84F	Clear ascii score pointed to by score
void addScoreA(int value, char *score);				// 0xF85E	Add value to ascii score

// delayB that supports unsigned numbers
void __attribute__((noinline)) delayBU(unsigned int cycles)
{
    asm(	"delayBU:"				);
    asm(	"	decb"				);
    asm(	"	bne		delayBU"	);
}

#define tstat (*((volatile unsigned int *) 0xc856))

#define pot0 (*((volatile int*) 0xc81b))
#define pot1 (*((volatile int *) 0xc81c))
#define pot2 (*((volatile int *) 0xc81d))
#define pot3 (*((volatile int *) 0xc81e))

#define epot0 (*((volatile unsigned int *) 0xc81f))
#define epot1 (*((volatile unsigned int *) 0xc820))
#define epot2 (*((volatile unsigned int *) 0xc821))
#define epot3 (*((volatile unsigned int *) 0xc822))

#define scale (*((volatile unsigned int *) 0xd004))		// 0xD004	Scale register on VIA

#define _BTN_LST_MASK (*((volatile unsigned int *) 0xc810))	// All buttons - last time
#define _BTN_CUR_MASK (*((volatile unsigned int *) 0xc811))	// All buttons - current
#define _JOY1_B1	0x01
#define _JOY1_B2	0x02
#define _JOY1_B3	0x04
#define _JOY1_B4	0x08
#define _JOY2_B1	0x10
#define _JOY2_B2	0x20
#define _JOY2_B3	0x40
#define _JOY2_B4	0x80

#define _SCR_BTM   -127
#define _SCR_TOP	127
#define _SCR_LEFT  -127
#define _SCR_RIGHT  127
#define _SCR_CTR    0

#endif