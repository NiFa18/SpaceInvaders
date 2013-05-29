/********************************************************************************************
 SpaceInvader Player Controls
 
 File        : SI_player.h
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 24.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Player Control Functions
 ********************************************************************************************/
#ifndef _GC_player_h
#define _GC_player_h

// ---- function declarations

void PL_drawPlayer(int y);      //draws player at x coordinate
void PL_moveLeft();             //moves player 1 px to the left
void PL_moveRight();            //moves player 1 px to the right
void test();

#endif
