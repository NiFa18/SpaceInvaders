/********************************************************************************************
 SpaceInvader Shot Controls
 
 File        : SI_controls.h
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 24.04.2013
 Last Update : 24.04.2013 Fabian Niedermann
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Shot Control Functions
 ********************************************************************************************/
#ifndef _GC_shot_h
#define _GC_shot_h

void SH_drawShot(int x);
void SH_moveShot(SI_shot shot);
void SH_removeShot(SI_shot shot);

#endif
