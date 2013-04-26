/*****************************************************************************
  SoftTimer for ARM-Platform with OKI-H5003
------------------------------------------------------------------------------  
  File        : SoftTimer.c
  Author      : Erwin Braendle    
  Date Issued : 30.04.2009
  Last Change : 04.05.2009 djust, HW-Timer und Timer-ISR hinzugefügt
  Target      : ESP Embedded System ARM-Platform
------------------------------------------------------------------------------  
  Description : This module offers a set of functions to handle SoftTimer 
                based Applications.
*****************************************************************************/

// --- Includes
#include "SoftTimer.h"
#include "target.h"
#include <stddef.h>

// --- Defines
#define DLY_122_US    0x0001    // 122.07us
#define   DLY_1_MS    0x0008    // 0.9765ms
#define   DLY_5_MS    0x0029    // 5.0049ms
#define  DLY_10_MS    0x0052    //10.0097ms
#define  DLY_20_MS    0x00a4    //20.0195ms
#define  DLY_30_MS    0x00f6    //30.0293ms
#define DLY_62_5_MS   0x0100    //62.5000ms

// --- Typedefs
typedef struct
{
  tSTmode mode;
  unsigned int     timeSet;
  unsigned int     timeRemain;
  void    (*pFkt)(void);
  int     running;
} tSoftTimer;

// --- Variables
tSoftTimer  timer[ST_COUNT];
long  interrupt_variable;

// --- Local Function Prototypes
void HW_TimerInit(int dly);

// --- Functional Implementation
void ST_Init (void)                                         
{
  int i;
  interrupt_variable = 0;

  for (i = 0; i < ST_COUNT; i++)
  {
    timer[i].mode = 0;
    timer[i].timeSet = 0;
    timer[i].timeRemain = 0;
    timer[i].pFkt = NULL;
    timer[i].running = 0;
  }
  
  HW_TimerInit(DLY_1_MS);
  
}


void ST_Tick (void)
{
  int i;

  for (i = ST_COUNT-1; i >=0; i--)
  {
    if (timer[i].running)
    {
      timer[i].timeRemain--;
      if (!(timer[i].timeRemain))
      {       
        timer[i].pFkt();
        switch (timer[i].mode)
        {
          case INTERVAL:
            timer[i].timeRemain = timer[i].timeSet;
            break;
          case ONESHOT:
            timer[i].running = 0;
            break;
          default:
            break;
        }
      }
    }  
  }
}


int ST_Create (tSTmode mode, void(*pFkt)(void))
{
  int i;

  for (i = ST_COUNT; i > 0; i--)
  {
    if (timer[i-1].mode == 0)
    {
      timer[i-1].mode = mode;
      timer[i-1].timeSet = 0;
      timer[i-1].timeRemain = timer[i-1].timeSet;
      timer[i-1].pFkt = pFkt;
      timer[i-1].running = 0;
      break;
    }  
  }
  return i;
}


int ST_Start (int id, int time)
{
  if ((id <= 0) || (id > ST_COUNT) || (timer[id-1].pFkt == NULL))
    return 0;

  timer[id-1].timeSet = time;
  timer[id-1].timeRemain = timer[id-1].timeSet;
  timer[id-1].running = (timer[id-1].timeSet > 0)? 1 : 0;
  return id;
}


int ST_Restart (int id)
{
  if ((id <= 0) || (id > ST_COUNT) || (timer[id-1].pFkt == NULL))
    return 0;

  timer[id-1].timeRemain = timer[id-1].timeSet;
  timer[id-1].running = (timer[id-1].timeSet > 0)? 1 : 0;
  return id;
}


int ST_Stop (int id)
{
  if ((id <= 0) || (id > ST_COUNT) || (timer[id-1].pFkt == NULL))
    return 0;

  timer[id-1].running = 0;
  return id;
}


int ST_Resume (int id)
{
  if ((id <= 0) || (id > ST_COUNT) || (timer[id-1].pFkt == NULL))
    return 0;

  timer[id-1].running = 1;
  return id;
}


int ST_Delete (int id)
{
  if ((id <= 0) || (id > ST_COUNT) || (timer[id-1].pFkt == NULL))
    return 0;

    timer[id-1].mode = 0;
    timer[id-1].timeSet = 0;
    timer[id-1].timeRemain = 0;
    timer[id-1].pFkt = NULL;
    timer[id-1].running = 0;
  return id;
}


// HW-Timer ISR
__declspec(interrupt) void HWTimerISR (void)
{
   interrupt_variable++;
   ST_Tick();
}

void HW_TimerInit (int dly)
{
    EXCEPT_VEC(VEC_PIT) = HWTimerISR;
    /*---- Tick initialization code goes HERE! --------------------------------------------------------*/
    PICR = 0x0100 | VEC_PIT;  /* priority = 1, Interruptvector = VEC_PIT                               */
    PITR = dly;               /* prescaler_val = 1, periodic interrupt timing modulus = 1  (0x0008)    */
                              /*                512 * [prescaler_value] * 4 * [modulus]                */
                              /* => period = ----------------------------------------- = 0.976 ms      */
                              /*                          frequency                                    */
                              
    asm{andi #0x201f,sr}       /*CPU Priorität auf tiefste Ebene, alle Interrupts akzeptiert*/
}



