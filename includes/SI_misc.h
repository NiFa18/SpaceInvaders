/********************************************************************************************
 SpaceInvaders Miscellanious Functions
 
 File        : SI_misc.h
 Author      : Christian Gwerder
 Date        : 17.04.2013
 Last Update : 17.04.2013 Christian Gwerder
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Allgemein verwendete Funktionen
 ********************************************************************************************/

#ifndef __SI_INTERRUPTS_H
#define __SI_INTERRUPTS_H

#include "SI_defines.h"

// --- Function Prototypes

inline static void DelayMs (int ms);
int initInterrupt(void);

#endif /* #ifndef __SI_INTERRUPTS_H */