/********************************************************************************************
 SpaceInvadors
 
 File        : main.c
 Author      : Christian Gwerder
 Date        : 17.04.2013
 Last Update : 22.04.2013 Christian Gwerder
 
 ChangeLog   : Erste Funktionialitaet erstellt (Timer, Tastendrucke), CG, 22.04.13
 Datei erstellt, CG, 17.04.13
 
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Hauptprogramm zu SpaceInvadors
 ********************************************************************************************/

#if 1

#include "target.h"
#include "SoftTimer.h"

#include "Types.h"
#include "SI_defines.h"
#include "SI_controls.h"

// Global Variables

SI_stateReg stateRegister;
int playerPositionX;    //Position of player on x-Axis
SI_shot shotArray[SI_MAXSHOTS];
SI_enemyLine enemyArray[SI_ENEMYLINES];


/***************************************************************************
 *   \brief main
 *   \return void
 ***************************************************************************/
void main (void)
{
    int timerHandlerArray[ST_COUNT];
    
    initInterrupt();
    ST_Init();
    GC_initGame();
    
    // Spiel aktualisieren
    timerHandlerArray[0] = ST_Create(INTERVAL, GC_setUpdate);
    timerHandlerArray[0] = ST_Start(timerHandlerArray[0], SI_REFRESHTIME);
    // Timer fuer Schuss-Verzoegerung
    timerHandlerArray[1] = ST_Create(ONESHOT, GC_clrWeaponDelay);
    
    
	while(1)
    {
        
        /*
         * Neustart bei entsprechendem Tastendruck
         */
        if(stateRegister.restart)
        {
            GC_initGame();
        }
        
        if(stateRegister.update)
        {
            GC_updateGame();
        }
        
        /*
         * Neuer Schuss absetzen
         */
        if(stateRegister.shoot & 0x02)
        {
            // Nur wenn Weapon Delay abgelaufen
            if(!(stateRegister.shoot & 0x04))
            {
                GC_shoot();
                stateRegister.shoot |= 0x04;		//WeaponDelay aktiviert
                timerHandlerArray[1] = ST_Start(timerHandlerArray[1], SI_DELAYWEAPON);
            }
            stateRegister.shoot &= 0x05;			//Bit von Schuss-Taste löschen
        }
        
        /*
         *  Spieler bewegen
         */ 
        if(stateRegister.move)
        {
            GC_movePlayer();
            stateRegister.move = 0;
        }
        /*
         *  Spiel fertig
         */
        if(stateRegister.finished)
        {
            DisplayWriteText ("Game finished",4,6);
            DisplayWriteText ("press USW3 to restart",7,3);
            DisplaySetPoint (150,10);
            DisplayFillArea (149,11,151,11);
            DisplayFillArea (148,12,152,12);
            DisplayFillArea (147,13,153,13);
            DisplayFillArea (146,14,154,14);
            DisplayFillArea (145,15,155,15);
            DisplayFillArea (149,16,151,25);
        }
        
 	}
}

#endif
