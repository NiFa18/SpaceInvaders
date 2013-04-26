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
    int absYPos = 70 - (rowNr*(EN_SYMBOLHEIGHT+2*EN_GAPWIDTH/3));   //calculate absolute y position of enemy line
    
    for (n=0; n < 8; n++)
    {
        enemyArray[rowNr].enemyLocations[6+5*n]=1;       //sets entries in enemy array according to horizontal enemy position
        enemyArray[rowNr].enemyLocations[7+5*n]=1;
        enemyArray[rowNr].enemyLocations[8+5*n]=1;        
        EN_drawEnemy(EN_INITIALXPOSITION+n*(EN_SYMBOLWIDTH+EN_GAPWIDTH),absYPos);
    }
}

void EN_removeEnemy(int rowNr, int colNr)       //colNr 0-47
{
    int absYPos = 70 - (rowNr*(EN_SYMBOLHEIGHT+2*EN_GAPWIDTH/3));   //calculate absolute y position of enemy line
    int absXPos = 8;                                                //if the enemy is to the very left
    int i;
    
    if ( !(enemyArray[rowNr].enemyLocations[colNr]==0))             //deletes enemy part at shot impact (if there is one)
    {
        absXPos += SI_PPAE*colNr;        
        DisplayClrArea(absXPos, absYPos, absXPos+2, absYPos+5);
        enemyArray[rowNr].enemyLocations[colNr]=0;
        
        if ( !(enemyArray[rowNr].enemyLocations[colNr-1]==0))       //deletes enemy parts left of shot impact
        {
            DisplayClrArea(absXPos-SI_PPAE, absYPos, absXPos-SI_PPAE+2, absYPos+5);
            enemyArray[rowNr].enemyLocations[colNr-1]=0;
            
            if ( !(enemyArray[rowNr].enemyLocations[colNr-2]==0))
            {
                DisplayClrArea(absXPos-2*SI_PPAE, absYPos, absXPos-2*SI_PPAE+2, absYPos+5);
                enemyArray[rowNr].enemyLocations[colNr-2]=0;
            }
            
        }

        if ( !(enemyArray[rowNr].enemyLocations[colNr+1]==0))       //deletes enemy parts right of shot impact
        {
            DisplayClrArea(absXPos+SI_PPAE, absYPos, absXPos+SI_PPAE+2, absYPos+5);
            enemyArray[rowNr].enemyLocations[colNr+1]=0;
            
            if ( !(enemyArray[rowNr].enemyLocations[colNr+2]==0))
            {
                DisplayClrArea(absXPos+2*SI_PPAE, absYPos, absXPos+2*SI_PPAE+2, absYPos+5);
                enemyArray[rowNr].enemyLocations[colNr+2]=0;
            }

        }
        
    }

}
