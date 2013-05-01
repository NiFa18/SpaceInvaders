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

//global variables

extern SI_enemyLine enemyArray[SI_ENEMYLINES];

/***************************************************************************
 *   \brief draws enemy at position x,y
 *   \return void
 ***************************************************************************/
void EN_drawEnemy(int x, int y)
{
    DisplayFillArea(x, y, x+8, y+5);
    DisplayClrPoint(x, y+4);
    DisplayClrPoint(x+2, y+3);
    DisplayClrPoint(x+4, y+1);
    DisplayClrPoint(x+6, y+3);
    DisplayClrPoint(x+8, y+4);
    DisplayClrArea(x, y+1, x+1, y+1);
    DisplayClrArea(x, y+5, x+2, y+5);
    DisplayClrArea(x+2, y, x+6, y);
    DisplayClrArea(x+6, y+5, x+8, y+5);
    DisplayClrArea(x+7, y+1, x+8, y+1);
}

/***************************************************************************
 *   \brief draws enemy line at position x,y
 *   \return void
 ***************************************************************************/
void EN_drawEnemyLine(int rowNr)
{
    int n;
    //calculate absolute y position of enemy line
    int absYPos = 70 - (rowNr*(EN_SYMBOLHEIGHT+EN_GAPHEIGHT));
    
    for (n=0; n < 8; n++)
    {
        //sets entries in enemy array according to horizontal enemy position
        enemyArray[rowNr].enemyLocations[5+5*n]=1;
        enemyArray[rowNr].enemyLocations[6+5*n]=1;
        enemyArray[rowNr].enemyLocations[7+5*n]=1;        
        EN_drawEnemy(EN_INITIALXPOSITION+n*(EN_SYMBOLWIDTH+EN_GAPWIDTH),absYPos);
    }
}

/***************************************************************************
 *   \brief removes enemy at row number and in collumn where the shot impacts
 *   \return void
 ***************************************************************************/
void EN_removeEnemy(int rowNr, int colNr)
{
    //calculate absolute y position of enemy line
    int absYPos = 70 - (rowNr*(EN_SYMBOLHEIGHT+EN_GAPHEIGHT));
    //if the enemy is to the very left
    int absXPos = EN_SIDEBORDER;
    int i;
    
    //deletes enemy part at shot impact (if there is one)
    if ( !(enemyArray[rowNr].enemyLocations[colNr]==0))
    {
        absXPos += SI_PPAE*colNr;        
        DisplayClrArea(absXPos, absYPos, absXPos+2, absYPos+5);
        enemyArray[rowNr].enemyLocations[colNr]=0;
        
        //deletes enemy parts left of shot impact
        if ( !(enemyArray[rowNr].enemyLocations[colNr-1]==0))
        {
            DisplayClrArea(absXPos-SI_PPAE, absYPos, absXPos-SI_PPAE+2, absYPos+5);
            enemyArray[rowNr].enemyLocations[colNr-1]=0;
            
            if ( !(enemyArray[rowNr].enemyLocations[colNr-2]==0))
            {
                DisplayClrArea(absXPos-2*SI_PPAE, absYPos, absXPos-2*SI_PPAE+2, absYPos+5);
                enemyArray[rowNr].enemyLocations[colNr-2]=0;
            }
            
        }

        //deletes enemy parts right of shot impact
        if ( !(enemyArray[rowNr].enemyLocations[colNr+1]==0))
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
