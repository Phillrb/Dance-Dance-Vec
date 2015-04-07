//
//  beats.h
//
//  Created by Phillip Riscombe-Burton on 05/04/2015.
//  Copyright (c) 2015 Phillip Riscombe-Burton. All rights reserved.
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

#ifndef _BEATS_H
#define _BEATS_H

#pragma once

typedef enum{
    PRBArrowUp = 1,
    PRBArrowRight = 1 << 1,
    PRBArrowDown = 1 << 2,
    PRBArrowLeft = 1 << 3,
    PRBArrowUpHeld = 1 << 4,        //will add a dash after an arrow
    PRBArrowRightHeld = 1 << 5,     //to indicate user should rapidly tap for duration
    PRBArrowDownHeld = 1 << 6,
    PRBArrowLeftHeld = 1 << 7
} PRBArrow;

//These are the 'arrow beats' for a song
const int song1[82] =
{
    PRBArrowUp,
    0,
    0,
    PRBArrowUp,
    0,
    0,
    PRBArrowDown,
    0,
    0,
    PRBArrowDown, //10
    0,
    0,
    PRBArrowUp | PRBArrowDown,
    0,
    0,
    PRBArrowLeft,
    0,
    0,
    PRBArrowLeft,
    0,  //20
    0,
    PRBArrowRight,
    0,
    0,
    PRBArrowRight,
    0,
    0,
    PRBArrowLeft | PRBArrowRight,
    0,
    PRBArrowUp, //30
    PRBArrowDown,
    PRBArrowLeft,
    PRBArrowRight,
    0,
    0,
    0,
    0,
    PRBArrowRight,
    PRBArrowLeft,
    PRBArrowDown,   //40
    PRBArrowUp,
    0,
    0,
    PRBArrowUp,
    PRBArrowUp,
    PRBArrowDown,
    PRBArrowDown,
    PRBArrowLeft,
    PRBArrowRight,
    PRBArrowLeft,   //50
    PRBArrowRight,
    0,
    PRBArrowUp | PRBArrowRight,
    0,
    PRBArrowDown | PRBArrowLeft,
    0,
    0,
    PRBArrowUpHeld,
    PRBArrowUp,
    0,              //60
    PRBArrowDownHeld,
    PRBArrowDown,
    0,
    PRBArrowLeftHeld,
    PRBArrowLeft,
    0,
    PRBArrowRightHeld,
    PRBArrowRight,
    0,
    PRBArrowUpHeld | PRBArrowDownHeld,          //70
    PRBArrowUp | PRBArrowDown,
    PRBArrowRight,
    PRBArrowRight,
    0,
    0,
    PRBArrowLeftHeld |PRBArrowRightHeld,
    PRBArrowLeft | PRBArrowRight,
    PRBArrowUp,
    PRBArrowUp,
    0,      //80
    0,
    0
};


#endif


