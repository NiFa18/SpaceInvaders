/********************************************************************************************
 SpaceInvadors Player Functions
 
 File        : GC_player.c
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 26.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 
 ChangeLog   :
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Implementation of player control functions
 ********************************************************************************************/

#include "GC_player.h"

#include "SI_defines.h"
#include "displayNeu.h"

//global variables

extern int playerPositionX;

/***************************************************************************
 *   \brief draws player at position x
 *   \return void
 ***************************************************************************/
void PL_drawPlayer(int x)
{
    DisplayFillArea(x, PL_POSITIONY, x+10, PL_POSITIONY+5);
    DisplayClrArea(x, PL_POSITIONY+4, x+3, PL_POSITIONY+5);
    DisplayClrArea(x+7, PL_POSITIONY+4, x+10, PL_POSITIONY+5);
    DisplayClrPoint(x, PL_POSITIONY+3);
    DisplayClrPoint(x+4, PL_POSITIONY+5);
    DisplayClrPoint(x+6, PL_POSITIONY+5);
    DisplayClrPoint(x+10, PL_POSITIONY+3);
}

/***************************************************************************
 *   \brief moves player 1px to the left
 *   \return void
 ***************************************************************************/
void PL_moveLeft()
{
    playerPositionX--;
    DisplayClrArea(playerPositionX+11, PL_POSITIONY, playerPositionX+10, PL_POSITIONY+2);
    DisplayClrPoint(playerPositionX+10, PL_POSITIONY+3);
    DisplayClrPoint(playerPositionX+7, PL_POSITIONY+4);
    DisplayClrPoint(playerPositionX+6, PL_POSITIONY+5);
    DisplaySetPoint(playerPositionX+5, PL_POSITIONY+5);
    DisplaySetPoint(playerPositionX+4, PL_POSITIONY+4);
    DisplaySetPoint(playerPositionX+1, PL_POSITIONY+3);
    DisplayFillArea(playerPositionX, PL_POSITIONY, playerPositionX, PL_POSITIONY+2);
}

/***************************************************************************
 *   \brief moves player 1px to the right
 *   \return void
 ***************************************************************************/
void PL_moveRight()
{
    DisplayClrArea(playerPositionX, PL_POSITIONY, playerPositionX, PL_POSITIONY+2);
    DisplayClrPoint(playerPositionX+1, PL_POSITIONY+3);
    DisplayClrPoint(playerPositionX+4, PL_POSITIONY+4);
    DisplayClrPoint(playerPositionX+5, PL_POSITIONY+5);
    DisplaySetPoint(playerPositionX+6, PL_POSITIONY+5);
    DisplaySetPoint(playerPositionX+7, PL_POSITIONY+4);
    DisplaySetPoint(playerPositionX+10, PL_POSITIONY+3);
    DisplayFillArea(playerPositionX+11, PL_POSITIONY, playerPositionX+10, PL_POSITIONY+2);
    playerPositionX++;
}
