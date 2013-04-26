/********************************************************************************************
 SpaceInvadors Enemy Functions
 
 File        : GC_enemy.c
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 26.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 
 ChangeLog   :  
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Implementation of enemy control functions
 ********************************************************************************************/

#include "GC_enemy.h"
#include "SI_defines.h"
#include "displayNeu.h"

extern SI_enemyLine enemyArray[SI_ENEMYLINES];

void EN_drawEnemy(int x, int y)
{
    DisplayFillArea (x, y, x+8, y+5);
}

void EN_drawEnemyLine(int rowNr)
{
    int n;          //Enemy #
    int absYPos = 70 - (rowNr*(EN_SYMBOLHEIGHT+2*EN_GAPWIDTH/3));
    
    for (n=0; n < 8; n++)
    {
        enemyArray[rowNr].enemyLocations[6+5*n]=1;       //sets entries in enemy array according to horizontal enemy position
        enemyArray[rowNr].enemyLocations[7+5*n]=1;
        enemyArray[rowNr].enemyLocations[8+5*n]=1;        
        EN_drawEnemy(EN_INITIALXPOSITION+n*(EN_SYMBOLWIDTH+EN_GAPWIDTH),absYPos);
    }
}

/*void EN_removeEnemy(int rowNr, int colNr)       //colNr 0-47
{
    int absYPos = 70 + (rowPos*9);
    DisplayClrRect(
}
*/