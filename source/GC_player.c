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
#include "displayNeu.h"

extern int playerPositionX;

void PL_drawPlayer(int x)
{
    DisplayFillArea(x, PL_POSITIONY, x+10, PL_POSITIONY+5);
}

void PL_moveLeft()
{
    playerPositionX--;
    DisplayDrawLine(playerPositionX, PL_POSITIONY, playerPositionX, PL_POSITIONY+5)
    DisplayClrLine(playerPositionX+PL_SYMBOLWIDTH, PL_POSITIONY,playerPositionX+PL_SYMBOLWIDTH, PL_POSITIONY+5)
}

void PL_moveRight()
{
    DisplayClrLine(playerPositionX, PL_POSITIONY, playerPositionX, PL_POSITIONY+5)
    DisplayDrawLine(playerPositionX+PL_SYMBOLWIDTH, PL_POSITIONY,playerPositionX+PL_SYMBOLWIDTH, PL_POSITIONY+5)
    playerPositionX++;
}
