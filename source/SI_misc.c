/********************************************************************************************
 SpaceInvadors Miscellanious Functions
 
 File        : SI_misc.c
 Author      : Christian Gwerder
 Date        : 17.04.2013
 Last Update : 18.04.2013 Christian Gwerder
 Target      : MEGA332, MetroTRK and CodeWarrior
 
 Beschreibung: Definition der allgemein verwendeten Funktionen
 							 Darunter: Interrupts, Delays
 ********************************************************************************************/

#include "SI_misc.h"
#include "SI_defines.h"
#include "target.h"

// ---- Global Variable

extern SI_stateReg stateRegister;

/***************************************************************************
 *   \brief a simple busy delay
 *   \param int: time in ms
 *   \return void
 ***************************************************************************/
void DelayMs (int ms) //inline static
{
  int i;
  if((SYNCR & 0xff00) == 0x7f00)      //CPU runs @ 16MHz
  {
    for (i = 0; i < 800 * ms; i++)
    {
    }
  }
  else                                //CPU runs @ 25MHz
  {
    for (i = 0; i < 1200 * ms; i++)
    {
    }
  }
}

/***************************************************************************
*   \brief ISR for button USW0
*   \return void
***************************************************************************/
__declspec (interrupt) void Usw0ISR (void)    
{
  if (DIORead(USW0) == 1)
  {
    stateRegister.shoot ^= 0x02;
  }
  CISR &= ~(1 << USW0);                // clear interrupt flag
}


///***************************************************************************
// *   \brief ISR for button USW1
// *   \return void
// ***************************************************************************/
//__declspec (interrupt) void Usw1ISR (void)
//{
//  if (DIORead(USW1) == 1)
//  {
//    BEEPER = 0;
//  }
//  CISR &= ~(1 << USW1);                // clear interrupt flag
//}
//
///***************************************************************************
// *   \brief ISR for button USW2
// *   \return void
// ***************************************************************************/
//__declspec (interrupt) void Usw2ISR (void)
//{
//  if (DIORead(USW2))
//  {
//    ANZEIGE ^= 0x20;
//  }
//  CISR &= ~(1 << USW2);                // clear interrupt flag
//}

/***************************************************************************
 *   \brief ISR for button USW3
 *   \return void
 ***************************************************************************/
__declspec (interrupt) void Usw3ISR (void)
{
  if (DIORead(USW3))
  {
    stateRegister.restart ^= TRUE;
  }
  CISR &= ~(1 << USW3);                // clear interrupt flag
}

/***************************************************************************
 *   \brief ISR for ENC_A
 *   \return void
 ***************************************************************************/
__declspec (interrupt) void EncAISR (void)
{
  unsigned char mask;
  
  if (DIORead(ENC_A))
  {
    if (DIORead(ENC_B))
    {
      stateRegister.move = SI_MOVE_LEFT;
    }
    else
    {
      stateRegister.move = SI_MOVE_RIGHT;
    }
  }
  else
  {
    if (DIORead(ENC_B))
    {
      stateRegister.move = SI_MOVE_RIGHT;
    }
    else
    {
      stateRegister.move = SI_MOVE_LEFT;
    }
  }
  
  CISR &= ~(1 << ENC_A);                      // clear interrupt flag
}

/***************************************************************************
 *   \brief ISR for ENC_B
 *   \return void
 ***************************************************************************/
__declspec (interrupt) void EncBISR (void)
{
  CISR &= ~(1 << ENC_B);                      // clear interrupt flag
}


/***************************************************************************
 *   \brief setup/enable button and encoder interrupts
 *   \return int: 1 - no Error
 ***************************************************************************/
int initInterrupt (void)
{
  TPUMCR = 0x0080 | ARB_TPU;                // user access, iarb = 0x04
  TICR   = 0x0200 | VEC_TPU;                // int level = 2, set Base Vector 0x80
  
  DIOInit(USW0, INPUT);                     // init USW0 as input port
  //DIOInit(USW1, INPUT);                     // init USW1 as input port
  //DIOInit(USW2, INPUT);                     // init USW2 as input port
  DIOInit(USW3, INPUT);                     // init USW3 as input port
  DIOInit(ENC_A, INPUT);                    // init ENC_A as input port
  DIOInit(ENC_B, INPUT);                    // init ENC_B as input port
  
  EXCEPT_VEC(VEC_TPU + USW0) = Usw0ISR;     // Initialize vectortable and assign function
  //EXCEPT_VEC(VEC_TPU + USW1) = Usw1ISR;     // Initialize vectortable and assign function
  //EXCEPT_VEC(VEC_TPU + USW2) = Usw2ISR;     // Initialize vectortable and assign function
  EXCEPT_VEC(VEC_TPU + USW3) = Usw3ISR;     // Initialize vectortable and assign function
	EXCEPT_VEC(VEC_TPU + ENC_A) = EncAISR;    // Initialize vectortable and assign function
  EXCEPT_VEC(VEC_TPU + ENC_B) = EncBISR;    // Initialize vectortable and assign function
  
  asm{andi #0x201f,sr}                      // CPU Priorit‰t auf tiefste Ebene, alle Interrupts akzeptiert
  return (1);
}