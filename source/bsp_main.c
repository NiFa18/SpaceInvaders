/********************************************************************************************
  Interrupts

  File        : main.c
  Author      : Danilo Just
  Date        : 14.04.2010
  Last Update : 14.04.2010 djust@hsr.ch
  Target      : MEGA332, BDM and CodeWarrior
  
  Beschreibung: Startup für das Miniprojekt im Modul Computertechnik. Demo für Softtimer,
                Button-Interrupts, Encoder-Interrupts und Displayfunktionen
********************************************************************************************/

#if 0

#include "target.h"
#include "DIO.h"
#include "displayNeu.h"
#include "SoftTimer.h"


// Funktions-Prototypen
int initInterrupt(void);

unsigned int counter = 0;

/***************************************************************************
*   \brief a simple busy delay
*   \param int: time in ms
*   \return void
***************************************************************************/
inline static void DelayMs (int ms)
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
*   \brief a simple function for the softtimer
*   \return void
***************************************************************************/
void fkt0(void)
{
   ANZEIGE ^= 0x40;            
}

/***************************************************************************
*   \brief a simple function for the softtimer
*   \return void
***************************************************************************/
void fkt1(void)
{
   ANZEIGE ^= 0x80;   
}


/***************************************************************************
*   \brief main
*   \return void
***************************************************************************/
void main (void)
{    
   int handlerArray[ST_COUNT];
   
   ANZEIGE = 0x00;

   
   initInterrupt();                                  // initialize interrupts
   ST_Init();                                        // initialize SoftTimer and HW-1ms ISR
   DisplayInit();                                    // initialize display driver

   handlerArray[0] = ST_Create(INTERVAL, fkt0);  
   handlerArray[1] = ST_Create(INTERVAL, fkt1);  
  
   handlerArray[0] = ST_Start(handlerArray[0], 700); // 700 ms
   handlerArray[1] = ST_Start(handlerArray[1], 800); // 800 ms

  while(1)
  {
     // test some dislay functions
	 DisplayDrawCircle(30, 40, 20);
     DelayMs(1000);
     DisplayClearCircle(30, 40, 20);
     DelayMs(1000);
     DisplayDrawFullCircle(30, 40, 20);
     DelayMs(1000);
     DisplayClrArea(20, 30, 40, 50);
     DelayMs(1000);
     DisplayDrawFullCircle(30, 40, 10);
     DelayMs(1000);
     DisplayClearFullCircle(30, 40, 20);
     DelayMs(1000);
     DisplayDrawCircle(120, 35, 30);
     DelayMs(1000);
     DisplayClearCircle(120, 35, 30);
     DelayMs(1000);
     DisplayDrawFullCircle(90, 35, 30);
     DelayMs(1000);
     DisplayClearFullCircle(90, 35, 15);
     DelayMs(1000);
     DisplayClearFullCircle(90, 35, 30);
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
    BEEPER = 1;
  }
  CISR &= ~(1 << USW0);                // clear interrupt flag
}

/***************************************************************************
*   \brief ISR for button USW1
*   \return void
***************************************************************************/
__declspec (interrupt) void Usw1ISR (void)   
{
  if (DIORead(USW1) == 1)
  {
    BEEPER = 0;
  }
  CISR &= ~(1 << USW1);                // clear interrupt flag
}

/***************************************************************************
*   \brief ISR for button USW2
*   \return void
***************************************************************************/
__declspec (interrupt) void Usw2ISR (void)    
{
  if (DIORead(USW2))
  {
    ANZEIGE ^= 0x20;
  }
  CISR &= ~(1 << USW2);                // clear interrupt flag
}

/***************************************************************************
*   \brief ISR for button USW3
*   \return void
***************************************************************************/
__declspec (interrupt) void Usw3ISR (void)   
{
  if (DIORead(USW3))
  {
    ANZEIGE ^= 0x10;
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
      counter--;
    }
	else
	{
      counter++;
	}
  } 
  else
  {
    if (DIORead(ENC_B))
	{
      counter++;
    }
	else
	{
      counter--;
	}
  }
  
  mask = (ANZEIGE & 0xF0);
  ANZEIGE = (mask | (((char)counter) & 0x0F));         // show counter on LED[3]...LED[0]
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
    DIOInit(USW1, INPUT);                     // init USW1 as input port                    
    DIOInit(USW2, INPUT);                     // init USW2 as input port                    
    DIOInit(USW3, INPUT);                     // init USW3 as input port                    
    DIOInit(ENC_A, INPUT);                    // init ENC_A as input port                   
    DIOInit(ENC_B, INPUT);                    // init ENC_B as input port 

    EXCEPT_VEC(VEC_TPU + USW0) = Usw0ISR;     // Initialize vectortable and assign function 
    EXCEPT_VEC(VEC_TPU + USW1) = Usw1ISR;     // Initialize vectortable and assign function 
    EXCEPT_VEC(VEC_TPU + USW2) = Usw2ISR;     // Initialize vectortable and assign function 
    EXCEPT_VEC(VEC_TPU + USW3) = Usw3ISR;     // Initialize vectortable and assign function 	
	EXCEPT_VEC(VEC_TPU + ENC_A) = EncAISR;    // Initialize vectortable and assign function 
    EXCEPT_VEC(VEC_TPU + ENC_B) = EncBISR;    // Initialize vectortable and assign function 

                  

    asm{andi #0x201f,sr}                      // CPU Priorität auf tiefste Ebene, alle Interrupts akzeptiert
    return (1);
}

#endif 