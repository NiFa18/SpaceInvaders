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

SI_enemyLine enemyArray[3];


/***************************************************************************
*   \brief main
*   \return void
***************************************************************************/
void main (void)
{
	DisplayInit();
    EN_drawEnemyLine(0);
    EN_drawEnemyLine(1);
    EN_drawEnemyLine(2);
	EN_removeEnemy(0,6);
	EN_removeEnemy(0,12);
	EN_removeEnemy(0,21);
	EN_removeEnemy(0,25);
	EN_removeEnemy(0,26);
	EN_removeEnemy(0,28);
	EN_removeEnemy(1,7);
	EN_removeEnemy(1,18);
	EN_removeEnemy(1,23);
	EN_removeEnemy(1,29);
	EN_removeEnemy(1,32);
	EN_removeEnemy(1,38);
	EN_removeEnemy(2,10);
	EN_removeEnemy(2,19);
	EN_removeEnemy(2,24);
	EN_removeEnemy(2,27);
	EN_removeEnemy(2,30);
	EN_removeEnemy(2,34);
}
#endif

