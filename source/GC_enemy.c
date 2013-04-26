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
    DisplayDrawRect (x, y, x+5, y+8);
}

void EN_drawEnemyLine(int rowNr, int x)
{
    int n;          //Enemy #
    int absYPos = 70 - (rowPos*9);
    
    for (n=0; n < 8; n++)
    {
        enemyArray[10+4*n]=1;       //sets entries in enemy array according to horizontal enemy position
        enemyArray[11+4*n]=1;
        enemyArray[12+4*n]=1;        
        EN_drawEnemy(x+n*11,absYPos);
    }
}

/*void EN_removeEnemy(int rowNr, int colNr)       //colNr 0-47
{
    int absYPos = 70 + (rowPos*9);
    DisplayClrRect(
}
*/