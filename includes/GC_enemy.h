/********************************************************************************************
 SpaceInvader Enemy Controls
 
 File        : SI_enemy.h
 Author      : Fabian Niedermann, Christian Gwerder
 Date        : 24.04.2013
 Last Update : 26.04.2013 Fabian Niedermann
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Shot Control Functions
 ********************************************************************************************/
#ifndef _GC_enemy_h
#define _GC_enemy_h

// ---- function declarations

void EN_drawEnemyLine(int rowNr);           //rowNr resembles row number from top down (0-3)
void EN_removeEnemy(int rowNr, int colNr);  //colNr resembles column number from 0-47

#endif
