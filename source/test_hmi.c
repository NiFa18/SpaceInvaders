/********************************************************************************************
  SpaceInvadors

  File        : test_hmi.c
  Author      : Christian Gwerder
  Date        : 21.04.2013
  Last Update : 21.04.2013 Christian Gwerder
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Test der Bedienung mit Taste und Drehschalter zu SpaceInvadors
********************************************************************************************/
#if 0

#include "target.h"
#include "SI_defines.h"
#include "Types.h"
#include "DIO.h"
#include "displayNeu.h"
#include "SoftTimer.h"

// Global Variables

SI_stateReg stateRegister;

/***************************************************************************
 *   \brief a simple function for the softtimer
 *   \return void
 ***************************************************************************/
void fkt0(void)
{
  printf("Interval-Timer mit 10s ausgeloest\n");
}

/***************************************************************************
 *   \brief a simple function for the softtimer
 *   \return void
 ***************************************************************************/
void fkt1(void)
{
  stateRegister.shoot &= 0x3;
}


/***************************************************************************
*   \brief main
*   \return void
***************************************************************************/
void main (void)
{

  int timerHandlerArray[ST_COUNT];
  
  initInterrupt();
  ST_Init();
  
  timerHandlerArray[0] = ST_Create(INTERVAL, fkt0);
  timerHandlerArray[1] = ST_Create(ONESHOT, fkt1);
  timerHandlerArray[0] = ST_Start(timerHandlerArray[0], 10000); // 10s
  
  
	while(1)
  {
    if(stateRegister.restart)
    {
      printf("Restart Taste geduerckt\n");
      stateRegister.restart = 0;
    }
    
    if(stateRegister.shoot & 0x02)
    {	
      printf("Schuss-Taste gedrueckt");
      if(!(stateRegister.shoot & 0x04))
      {
      	printf(" - Schuss abgesetzt");
      	stateRegister.shoot |= 0x04;		//WeaponDelay aktiviert
      	timerHandlerArray[1] = ST_Start(timerHandlerArray[1], 500); // 0.5s
      }
      printf("\n");
      stateRegister.shoot &= 0x05;			//Bit von Schuss-Taste l￶schen
    }
    
    if(stateRegister.move)
    {
      printf("An Drehschalter gedreht: ");
      if(stateRegister.move & SI_MOVE_LEFT)
        printf("Nach links\n");
      
      else if(stateRegister.move & SI_MOVE_RIGHT)
        printf("Nach rechts\n");
               
      else
        printf("Fehler\n");
      
      stateRegister.move = 0;
    }
 	}
}
#endif

