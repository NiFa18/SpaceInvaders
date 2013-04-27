/********************************************************************************************
 SpaceInvader Shot Controls
 
 File        : SI_shot.h
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 24.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Shot Control Functions
 ********************************************************************************************/
#ifndef _GC_shot_h
#define _GC_shot_h

#include "SI_defines.h"

// ---- function declarations

void SH_drawShot(int shotNr);
void SH_moveShot(int shotNr);
void SH_removeShot(int shotNr);

#endif
