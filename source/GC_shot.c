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

/***************************************************************************
 *   \brief draws shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_drawShot(SI_shot shot)
{
    DisplaySetPoint(shot.x, shot.y);
    DisplaySetPoint(shot.x, shot.y+1);
}

/***************************************************************************
 *   \brief moves shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_moveShot(SI_shot shot)
{
    DisplayClrPoint(shot.x, shot.y);
    DisplaySetPoint(shot.x, shot.y+2);
}

/***************************************************************************
 *   \brief removes shot according to shot position
 *   \return void
 ***************************************************************************/
void SH_removeShot(SI_shot shot)
{
    DisplayClrPoint(shot.x, shot.y);
}
