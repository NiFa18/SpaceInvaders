/********************************************************************************************
  SpaceInvadors

  File        : test_display.c
  Author      : Fabian Niedermann
  Date        : 26.04.2013
  Last Update : 26.04.2013 Fabian Niedermann
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Test des Displays
********************************************************************************************/
#if 0

#include "target.h"
#include "SI_defines.h"
#include "Types.h"
#include "DIO.h"
#include "displayNeu.h"
#include "SoftTimer.h"
#include "GC_enemy.h"
#include "stdio.h"


// Global Variables

SI_stateReg stateRegister;
int playerPositionX;    //Position of player on x-Axis
SI_shot shotArray[SI_MAXSHOTS];
SI_enemyLine enemyArray[SI_ENEMYLINES];


/***************************************************************************
*   \brief main
*   \return void
***************************************************************************/
void main (void)
{
	DisplayInit();
    EN_drawEnemyLine(0);
	EN_removeEnemy(0,6);
	EN_removeEnemy(0,12);
	EN_removeEnemy(0,21);
	EN_removeEnemy(0,25);
	EN_removeEnemy(0,26);
	EN_removeEnemy(0,28);
    DisplayDrawRect(4,4,155,9);
    DisplayDrawRect(8,12,151,75);
}
#endif

