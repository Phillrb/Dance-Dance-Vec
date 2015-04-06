//
//  main.c
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

// C protoypes for Vectrex exec functions
#include "vectrex.h"
#include "main.h"
#include "graphics.h"
#include "stdbool.h"
#include "sound.h"
#include "beats.h"

// NOTE: I think because we are using the -mint8 compiler flag, we don't need
//		 to explictly use the int8 type all the time, which gets syntax colouring
//		 back. Yay!

const int drawScaleSprite = 0x40;
const int drawScaleScreen = 0xFF;
const int screenMax = 63;
const int lastSlotPos = 80;

const int arrowSlotWidth = 20;
const int player1UpArrowYPos = 54;
const int player1RightArrowYPos = 42;
const int player1DownArrowYPos = 30;
const int player1LeftArrowYPos = 18;
const int player2UpArrowYPos = -18;
const int player2RightArrowYPos = -30;
const int player2DownArrowYPos = -42;
const int player2LeftArrowYPos = -54;

const int pressCountDownMax = 15;


// Main entry point and game loop
int main()
{
    int i = 0;
    int j = 0;
    int a = 0; //general purpose variable
    
    int arrowScale = drawScaleSprite;
    
    int upArrowPlayer1ButtonPressCountDown = pressCountDownMax;
    int rightArrowPlayer1ButtonPressCountDown = pressCountDownMax;
    int downArrowPlayer1ButtonPressCountDown = pressCountDownMax;
    int leftArrowPlayer1ButtonPressCountDown = pressCountDownMax;
    int upArrowPlayer2ButtonPressCountDown = pressCountDownMax;
    int rightArrowPlayer2ButtonPressCountDown = pressCountDownMax;
    int downArrowPlayer2ButtonPressCountDown = pressCountDownMax;
    int leftArrowPlayer2ButtonPressCountDown = pressCountDownMax;
    
    int framesUntilArrowSpawn = 0;
    int maxFramesUntilArrowSpawn = 20;
    
    int songPos = 0;
    bool spawnNextArrows = true;
    int offsetXArrowsSinceSpawn = 0;
    
    int arrowSlots[6] = {0};    //there are currently 6 columns (slots) of arrows
                                //they creep left together and then reset to their 1st positions and then repeat
    int noOfArrowSlots = sizeof(arrowSlots);

    int hitLineXPos = lastSlotPos - (maxFramesUntilArrowSpawn / 2) - ((noOfArrowSlots - 1) * arrowSlotWidth);
    
    int currentColXPos = 0;
    int currentIntensity = 0x5F;
    
    bool isPlayer1 = true;
    
    //Initial settings
    intensA(0x5F);
    reset0Ref();
    scale = drawScaleScreen;
    moveToD(0,0);
    
    //main loop
    while (true)
    {
        //TODO currently sound does not work!!!
        initMusicCHK(player_fire_sound);
        
        // wait for frame boundary (one frame = 30,000 cyles = 50 Hz)
        waitRecal();
        
        //TODO currently sound does not work!!!
        doSound();
        
        //reset drawing ref
        reset0Ref();
        scale = drawScaleScreen;
        
        //Draw hit line and divider
        intensA(0x2F);
        //Divider (horizontal)
        moveToD(screenMax, 0);
        drawLineD((-2 * screenMax), 0);
        
        //hit line (vertical)
        reset0Ref();
        intensA(0x1F);
        moveToD(hitLineXPos,0);
        moveToD(0, screenMax);
        drawLineD(0, (-2 * screenMax));
        
        //Reset drawing ref etc
        reset0Ref();
        intensA(0x5F);
        
        //Put next arrows into last slot (far right)?
        if(spawnNextArrows)
        {
            spawnNextArrows = false;
            offsetXArrowsSinceSpawn = 0;
            
            //Cascade arrows down the slots
            for(i = 0; i < noOfArrowSlots - 1; i++)
            {
                arrowSlots[i] = arrowSlots[i+1];
            }
            
            //Add new arrows to last slot
            arrowSlots[noOfArrowSlots - 1] = song1[songPos];
        }
        
        //Display all arrows in queue at correct locations
        for(i = 0; i < noOfArrowSlots; i++)
        {
            //Get target col - THIS IS CURRENTLY THE SOURCE FOR BOTH PLAYERS REGARDLESS OF SELECTED SKILL LEVEL
            a = arrowSlots[i];
        
            //Get Xpos - this is how far the slots have crept left from their original positions
            currentColXPos = lastSlotPos - offsetXArrowsSinceSpawn - ((noOfArrowSlots - i) * arrowSlotWidth);
            
            //Scale & intensity of arrows - used to make arrows shrink away to the left of the vertical hit line
            if(i == 0)
            {
                arrowScale = drawScaleSprite - (framesUntilArrowSpawn * 2);
                
                currentIntensity = framesUntilArrowSpawn * 5;
                if(currentIntensity > 0x5F) currentIntensity = 0x5F;
                intensA(0x5F - currentIntensity);
            }
            else
            {
                arrowScale = drawScaleSprite;
                intensA(0x5F);
            }
            
            //Draw arrows in slots for both players - currently using same source
            if(a & PRBArrowUp || a & PRBArrowUpHeld)
            {
                drawArrowAtPositionToScale(upArrow, currentColXPos, player1UpArrowYPos, arrowScale, a & PRBArrowUpHeld);
                drawArrowAtPositionToScale(upArrow, currentColXPos, player2UpArrowYPos, arrowScale, a & PRBArrowUpHeld);
            }
            
            if(a & PRBArrowRight || a & PRBArrowRightHeld)
            {
                drawArrowAtPositionToScale(rightArrow, currentColXPos, player1RightArrowYPos, arrowScale, a & PRBArrowRightHeld);
                drawArrowAtPositionToScale(rightArrow, currentColXPos, player2RightArrowYPos, arrowScale, a & PRBArrowRightHeld);
            }
            
            if(a & PRBArrowDown || a & PRBArrowDownHeld)
            {
                drawArrowAtPositionToScale(downArrow, currentColXPos, player1DownArrowYPos, arrowScale, a & PRBArrowDownHeld);
                drawArrowAtPositionToScale(downArrow, currentColXPos, player2DownArrowYPos, arrowScale, a & PRBArrowDownHeld);
            }
            
            if(a & PRBArrowLeft || a & PRBArrowLeftHeld)
            {
                drawArrowAtPositionToScale(leftArrow, currentColXPos, player1LeftArrowYPos, arrowScale, a & PRBArrowLeftHeld);
                drawArrowAtPositionToScale(leftArrow, currentColXPos, player2LeftArrowYPos, arrowScale, a & PRBArrowLeftHeld);
            }
            
            
        }
        
        //Arrow spawn control
        if(framesUntilArrowSpawn >= maxFramesUntilArrowSpawn)
        {
            framesUntilArrowSpawn = 0;
        
            songPos++;
            
            //Replay song forever
            if (songPos >= sizeof(song1))
            {
                //TODO MAKE RESET FUNC
                songPos = 0;
                
            }
            
            spawnNextArrows = true;
        }
        
        framesUntilArrowSpawn++;
        offsetXArrowsSinceSpawn++;
        
        
        //User input
        readButton();
        
        //Player 1: check button press and show press action animation
        checkButtonPressAndAnimateConfirmation(true, _JOY1_B1, &upArrowPlayer1ButtonPressCountDown, player1UpArrowYPos, upArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(true, _JOY1_B2, &rightArrowPlayer1ButtonPressCountDown, player1RightArrowYPos, rightArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(true, _JOY1_B3, &downArrowPlayer1ButtonPressCountDown, player1DownArrowYPos, downArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(true, _JOY1_B4, &leftArrowPlayer1ButtonPressCountDown, player1LeftArrowYPos, leftArrow, hitLineXPos, arrowScale);

        //Player 2: check button press and show press action animation
        checkButtonPressAndAnimateConfirmation(false, _JOY2_B1, &upArrowPlayer2ButtonPressCountDown, player2UpArrowYPos, upArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(false, _JOY2_B2, &rightArrowPlayer2ButtonPressCountDown, player2RightArrowYPos, rightArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(false, _JOY2_B3, &downArrowPlayer2ButtonPressCountDown, player2DownArrowYPos, downArrow, hitLineXPos, arrowScale);
        checkButtonPressAndAnimateConfirmation(false, _JOY2_B4, &leftArrowPlayer2ButtonPressCountDown, player2LeftArrowYPos, leftArrow, hitLineXPos, arrowScale);
    }
}

//Draws an arrow at a particular location
void drawArrowAtPositionToScale(const int* arrow, int xPos, int yPos, int newScale, bool isHeld)
{
    reset0Ref();
    scale = drawScaleScreen;
    moveToD(xPos, yPos);
    scale = newScale;
    if(isHeld)
    {
        moveToD(20, 0);
        drawLineD(40,0);
        moveToD(-60, 0);
    }
    drawVLp(arrow,0);
}

//Check button press and show press action animation
void checkButtonPressAndAnimateConfirmation(bool isPlayer1, int button, int *buttonPressCountDown, int arrowYPos, const int arrow[], int hitLineXPos, int arrowScale)
{
    checkButtonPress(isPlayer1, button, buttonPressCountDown);
    displayConfirmationAnimation(buttonPressCountDown, arrowYPos, arrow, hitLineXPos, arrowScale);
}

//Check button press
void checkButtonPress(bool isPlayer1, int button, int *buttonPressCountDown){
    
    //Was button pressed by user?
    if(_BTN_CUR_MASK & button)
    {
        //Start press confirmation animation
        if(*buttonPressCountDown == pressCountDownMax) *buttonPressCountDown = *buttonPressCountDown - 1;
        
        //TODO check if correct and increment score! //USE isPlayer1.... possibly just pass score here to increment so this method has no idea the context of the player
    }
}

//Display the arrow pressed with an animation
void displayConfirmationAnimation(int *buttonPressCountDown, int arrowYPos, const int arrow[], int hitLineXPos, int arrowScale){
    
    //move this to func
    //Decrement button press action counter
    if(*buttonPressCountDown < pressCountDownMax)
    {
        *buttonPressCountDown = *buttonPressCountDown - 1;
        if(*buttonPressCountDown <= 0) *buttonPressCountDown = pressCountDownMax;
    }
    
    //show press action
    if(*buttonPressCountDown < pressCountDownMax)
    {
        reset0Ref();
        scale = drawScaleScreen;
        moveToD(hitLineXPos, arrowYPos);
        scale = arrowScale + (pressCountDownMax * 2) - (*buttonPressCountDown * 2);
        drawVLp(arrow,0);
    }
}

