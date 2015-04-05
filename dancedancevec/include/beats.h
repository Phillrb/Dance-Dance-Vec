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
    PRBArrowLeft = 1 << 3
} PRBArrow;


const unsigned int song1BeatHoldLengths[3][2] =
{
    3, 2, //Arrows at song pos 3 should be held for 2 beats
    15, 3,
    19, 2
};

const int song1[20] =
{
    PRBArrowDown,
    PRBArrowRight,
    PRBArrowUp,
    PRBArrowLeft,
    PRBArrowDown,                   //5
    PRBArrowDown,
    PRBArrowRight | PRBArrowLeft,
    PRBArrowUp | PRBArrowDown,
    PRBArrowRight | PRBArrowLeft,
    PRBArrowUp | PRBArrowDown,      //10
    0,
    PRBArrowRight | PRBArrowUp,
    PRBArrowRight | PRBArrowUp,
    PRBArrowLeft | PRBArrowUp,
    PRBArrowLeft | PRBArrowUp,      //15
    PRBArrowLeft | PRBArrowDown,
    PRBArrowLeft | PRBArrowDown,
    PRBArrowRight | PRBArrowDown,
    PRBArrowRight | PRBArrowDown,
    0                               //20
};


#endif


