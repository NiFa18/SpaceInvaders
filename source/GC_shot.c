/********************************************************************************************
 SpaceInvadors Shot Functions
 
 File        : GC_shot.c
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 26.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 
 ChangeLog   :
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Implementation of shot control functions
 ********************************************************************************************/

#include "GC_shot.h"

#include "SI_defines.h"
#include "displayNeu.h"

// Global Variables
extern SI_shot shotArray[SI_MAXSHOTS];

/***************************************************************************
 *   \brief draws shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_drawShot(int shotNr)
{
    DisplaySetPoint(shotArray[shotNr].x, shotArray[shotNr].y);
    DisplaySetPoint(shotArray[shotNr].x, shotArray[shotNr].y+1);
}

/***************************************************************************
 *   \brief moves shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_moveShot(int shotNr)
{
    if(shotArray[shotNr].y > SI_DISPHEIGHT-1)
    {
        SH_removeShot(shotNr);
    }
    else
    {
        DisplayClrPoint(shotArray[shotNr].x, shotArray[shotNr].y);
        DisplaySetPoint(shotArray[shotNr].x, shotArray[shotNr].y+2);
        shotArray[shotNr].y +=1;
    }
}

/***************************************************************************
 *   \brief removes shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_removeShot(int shotNr)
{
    DisplayClrPoint(shotArray[shotNr].x, shotArray[shotNr].y);
    shotArray[shotNr].x = 0;
    shotArray[shotNr].y = 0;
}
