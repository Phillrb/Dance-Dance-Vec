//
//  sound.h
//
//  Created by Phillip Riscombe-Burton on 05/04/2015.
//  Based upon original work by Martin White circa 2014
//  Information on playing sound for vectrex: 
//  http://vectrexmuseum.com/share/coder/html/soundplaying.htm
//
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

#ifndef _SOUND_H
#define _SOUND_H

#pragma once


const unsigned int player_fire_sound[] =
{
    0x1,
    2,12,                    //;;;;;;;;
    0,12,                    //; first byte is a note, to be
    2,12,                    //; found in vectrex rom, is a
    0,12,                    //; 64 byte table...
    2,6 ,                    //; last byte is length of note
    0,6,
    2,6,
    0,6,
    2,6,
    0,6,
    2,12,
    0,12,                    //;;;;;;;;
    2,12,
    0,12,
    2,12,
    0,12,                    //;;;;;;;;
    2,6,
    0,6,
    2,6,
    0,6,
    2,6,
    0,6,
    2,6,                    //;;;;;;;;
    0,6,
    2,12,
    0,12,
    19, 0x80                 //; $80 is end marker for music
                            //; (high byte set)
};


#endif


