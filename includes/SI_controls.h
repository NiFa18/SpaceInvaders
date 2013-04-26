/********************************************************************************************
  SpaceInvader Game Controls

  File        : SI_controls.h
  Author      : Fabian Niedermann, Christian Gwerder
  Date        : 20.04.2013
  Last Update : 20.04.2013 Fabian Niedermann
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: General Game Control Functions
********************************************************************************************/
#ifndef __SI_CONTROLS_H
#define __SI_CONTROLS_H

#include "Types.h"
#include "SI_defines.h"

// ---- function declarations

void GC_shoot();        //generates a shot at the current player position
void GC_initGame();     //initializes/restarts game (display, player position, enemies,...)
void GC_movePlayer();   //moves player on screen left or right
void GC_updateGame();   //updates game information (movement of shot, destruction of enemies,...)
void GC_clrWeaponDelay(); //clears WeaponDelay bit
 

#endif /* #ifndef __CONTROLS_H */