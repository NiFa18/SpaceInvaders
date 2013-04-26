/********************************************************************************************
  SpaceInvader Definitions

  File        : SI_defines.h
  Author      : Fabian Niedermann, Christian Gwerder
  Date        : 20.04.2013
  Last Update : 20.04.2013 Fabian Niedermann
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Allgemeine Definitionen zum SI-Project
********************************************************************************************/
#ifndef __SI_DEFINES_H
#define __SI_DEFINES_H

#include "Types.h"

// ---- Defines

#define SI_MOVE_LEFT        0x02
#define SI_MOVE_RIGHT       0x01
#define SI_DELAYWEAPON      500   //0.5s
#define SI_REFRESHTIME      500   //0.5s
#define SI_MAXSHOTS         10
#define SI_ENEMYLINES       1
#define SI_DISPWIDTH        160
#define SI_DISPHEIGHT       80
#define SI_PPAE             3       //PixelPerArrayEntry

#define PL_FIELDWIDTH       152
#define PL_SYMBOLWIDTH      11
#define PL_SYMBOLHEIGHT     6
#define PL_POSITIONY        4

#define EN_FIELDWIDTH       144
#define EN_SIDEBORDER       (SI_DISPWIDTH-EN_FIELDWIDTH)/2
#define EN_SYMBOLWIDTH      9
#define EN_SYMBOLHEIGHT     6
#define EN_GAPWIDTH         6
#define EN_LINEWIDTH        8*EN_SYMBOLWIDTH+7*EN_GAPWIDTH //93
#define EN_LOCATIONWIDTH    48
#define EN_TOPPOS           75
#define EN_INITIALXPOSITION 23

#define SH_WIDTH            1
#define SH_HEIGHT           2


// ---- Typedefs/Structs
 
typedef struct {
    uint8_t restart : 1;		/* Neustart = true */
    uint8_t shoot   : 3;		/* WeapenDelay = 1##; NeuerSchuss = #1#; Schuss unterwegs = ##1 */
    uint8_t move    : 2;		/* 10 = left; 01 = right; 00 = don't move  */
} SI_stateReg;

typedef struct {
    uint8_t x;                  //x and y position of a shot (lowest pixel of shot)
    uint8_t y;
} SI_shot;

typedef struct {
    int enemyLocations[EN_LOCATIONWIDTH];    //the enemy location on the screen (horizontal)
    //int y;                      //?y position of enemy line -> Nicht über Array Position bestimmt?
} SI_enemyLine;

#endif /* #ifndef __SI_DEFINES_H */