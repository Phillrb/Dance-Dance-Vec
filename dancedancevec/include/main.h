//
//  main.h
//  dancedancevec
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

#ifndef _MAIN_H
#define _MAIN_H

#include "stdbool.h"

//Draws an arrow
void drawArrowAtPositionToScale(const int* arrow, int xPos, int yPos, int newScale, bool isHeld);

//Displays the button pressed with an animation
void displayConfirmationAnimation(int *buttonPressCountDown, int arrowYPos, const int arrow[], int hitLineXPos, int arrowScale);

//Check if button pressed and start animation
void checkButtonPress(char* playerScore, int button, int *buttonPressCountDown);

//Check if button pressed and start animation and displays the button pressed with an animation
void checkButtonPressAndAnimateConfirmation(char* playerScore, int button, int *buttonPressCountDown, int arrowYPos, const int arrow[], int hitLineXPos, int arrowScale);


#endif
