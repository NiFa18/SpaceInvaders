/********************************************************************************************
  Digital I/O on TPU Channels MEGA332 (MC68332)

  File        : DIO.c
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 02.04.2002
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Mit diesem Code wird es ermöglicht digitale Signale über die TPU-Kanäle ein-
  zulesen, resp. auszugeben. Die Kanäle müssen entweder als Ein- oder Ausgänge initialisiert
  werden.
  
  examples      init TP0 as an output: DIOInit(0,TRUE);
                init TP1 as an input : DIOInit(1,FALSE);
                read from TP1        : val = DIORead(1);
                write to TP0         : DIOWrite(0,HIGH);

  execution time for "DIOInit()"  is about 41us
  execution time for "DIOWrite()" is about 19us
  execution time for "DIORead()"  is about 9us
********************************************************************************************/

/********************************************************************************************
  includes
********************************************************************************************/

#include "target.h"
#include "DIO.h"

int usw0, usw1, usw2, usw3;
extern int ctr;
/********************************************************************************************
  ISRs
********************************************************************************************/
__declspec (interrupt) void Usw0_Isr (void);
__declspec (interrupt) void Usw1_Isr (void);
__declspec (interrupt) void Usw2_Isr (void);
__declspec (interrupt) void Usw3_Isr (void);

/********************************************************************************************
  global functions
********************************************************************************************/

void DIOInit (int ch, int out)
/*
 * use this function to initialize a TPU channel
 * if "out", then channel "ch" is asserted as output-pin
 * if "!out", then channel "ch" is asserted as input-pin
*/
{
  if (ch == USW0)
  {
    EXCEPT_VEC(VEC_TPU + USW0) = Usw0_Isr;
    usw0 = NO_EDGE;
  }
  if (ch == USW1)    
  {
    EXCEPT_VEC(VEC_TPU + USW1) = Usw1_Isr;
    usw1 = NO_EDGE;
  }
  if (ch == USW2)    
  {
    EXCEPT_VEC(VEC_TPU + USW2) = Usw2_Isr;
    usw2 = NO_EDGE;
  }
  if (ch == USW3)    
  {
    EXCEPT_VEC(VEC_TPU + USW3) = Usw3_Isr;
    usw3 = NO_EDGE;
  }

  TPUMCR = 0x0080 | ARB_TPU;                  /* user access, iarb = 0x4                   */
  TICR   = 0x0500 | VEC_TPU;                  /* set Base Vector 0x80                      */

  switch (ch)
  {
    case 0:
    case 1:
    case 2:
    case 3:
         CFSR3 &= ~(0x000F << ch * 4);        /* clear                          */
         CFSR3 |=  (0x0008 << ch * 4);        /* select channel x DIO-mode      */
         HSQR1 &= ~(0x0003 << ch * 2);        /* update on transition           */
         if (out)
         {
           TPU_RAM(ch, 0) = 0x0003;           /* use pin for output             */
         }
         else
         {
           TPU_RAM(ch, 0) = 0x000F;           /* use input, detect either edge  */
         }
         HSRR1 |=  (0x0003 << ch * 2);        /* request inizialisation         */
         CPR1  &= ~(0x0003 << ch * 2);        /* clear                          */
         CPR1  |=  (0x0001 << ch * 2);        /* channel x priority low         */
         break;
    case 4:
    case 5:
    case 6:
    case 7:
         CFSR2 &= ~(0x000F << (ch - 4) * 4);  /* clear                          */
         CFSR2 |=  (0x0008 << (ch - 4) * 4);  /* select channel x DIO-mode      */
         HSQR1 &= ~(0x0003 << ch * 2);        /* update on transition           */
         if (out)
         {
           TPU_RAM(ch, 0) = 0x0003;           /* use pin for output             */
         }
         else
         {
           TPU_RAM(ch, 0) = 0x000F;           /* use input, detect either edge  */
         }
         HSRR1 |=  (0x0003 << ch * 2);        /* request inizialisation         */
         CPR1  &= ~(0x0003 << ch * 2);        /* clear                          */
         CPR1  |=  (0x0001 << ch * 2);        /* channel x priority low         */
         break;
    case 8:
    case 9:
    case 10:
    case 11:
         CFSR1 &= ~(0x000F << (ch - 8) * 4);  /* clear                          */
         CFSR1 |=  (0x0008 << (ch - 8) * 4);  /* select channel x DIO-mode      */
         HSQR0 &= ~(0x0003 << (ch - 8) * 2);  /* update on transition           */
         if (out)
         {
           TPU_RAM(ch, 0) = 0x0003;           /* use pin for output             */
         }
         else
         {
           TPU_RAM(ch, 0) = 0x000F;           /* use input, detect either edge  */
         }
         HSRR0 |=  (0x0003 << (ch - 8) * 2);  /* request inizialisation         */
         CPR0  &= ~(0x0003 << (ch - 8) * 2);  /* clear                          */
         CPR0  |=  (0x0001 << (ch - 8) * 2);  /* channel x priority low         */
         break;
    case 12:
    case 13:
    case 14:
    case 15:
         CFSR0 &= ~(0x000F << (ch - 12) * 4); /* clear                          */
         CFSR0 |=  (0x0008 << (ch - 12) * 4); /* select channel x DIO-mode      */
         HSQR0 &= ~(0x0003 << (ch - 8) * 2);  /* update on transition           */
         if (out)
         {
           TPU_RAM(ch, 0) = 0x0003;           /* use pin for output             */
         }
         else
         {
           TPU_RAM(ch, 0) = 0x000F;           /* use input, detect either edge  */
         }
         HSRR0 |=  (0x0003 << (ch - 8) * 2);  /* request inizialisation         */
         CPR0  &= ~(0x0003 << (ch - 8) * 2);  /* clear                          */
         CPR0  |=  (0x0001 << (ch - 8) * 2);  /* channel x priority low         */
         break;
  }
  CISR &= ~(0x0001 << ch);                    /* channel x int. n. asserted     */
  CIER |= (1 << ch);                 /* enable interrupt               */
}

void DIOWrite (int ch, int val)
/*
 * if val = TRUE  (!0) then HIGH is asserted to the corresponding channel
 * if val = FALSE (=0) then LOW is asserted to the corresponding channel
*/
{
  switch (ch)
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
         HSRR1 &= ~(0x0003 << ch * 2);        /* clear                          */
         if (val)
         {
           HSRR1 |= (0x0001 << ch * 2);       /* drive HIGH                     */
         }
         else{
           HSRR1 |= (0x0002 << ch * 2);       /* drive LOW                      */
         }
         break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
         HSRR0 &= ~(0x0003 << (ch - 8) * 2);  /* clear                          */
         if(val){
           HSRR0 |= (0x0001 << (ch - 8) * 2); /* drive HIGH                     */
         }
         else{
           HSRR0 |= (0x0002 << (ch - 8) * 2); /* drive LOW                      */
         }
        break;
  }
}

int DIORead (int ch)
/* returns bit 15 of TPU-RAM (PIN_LEVEL) */
{
  return (TPU_RAM(ch, 1) & 0x8000 ? 1 : 0);
}




void DIOInitAll (int out)
{
  DIOInit(USW0, out);                   // Initialize USW0 as Input/Output
  DIOInit(USW1, out);                   // Initialize USW0 as Input/Output
  DIOInit(USW2, out);                   // Initialize USW0 as Input/Output
  DIOInit(USW3, out);                   // Initialize USW3 as Input/Output
}


void DIOWriteAll (unsigned char val)
{
  (val & 0x01)? DIOWrite(USW0,TRUE) : DIOWrite(USW0,FALSE);
  val >>= 1;
  (val & 0x01)? DIOWrite(USW1,TRUE) : DIOWrite(USW1,FALSE);
  val >>= 1;
  (val & 0x01)? DIOWrite(USW2,TRUE) : DIOWrite(USW2,FALSE);
  val >>= 1;
  (val & 0x01)? DIOWrite(USW3,TRUE) : DIOWrite(USW3,FALSE);
}


unsigned char DIOReadAll (void)
{
  unsigned int inputs;
  
  inputs = 0x0000;
  inputs |= DIORead(USW3);
  inputs <<= 1;
  inputs |= DIORead(USW2);
  inputs <<= 1;
  inputs |= DIORead(USW1);
  inputs <<= 1;
  inputs |= DIORead(USW0); 
  return (unsigned char)inputs;   
}




__declspec (interrupt) void Usw0_Isr (void)
{
  if (DIORead(USW0))
    usw0 = RISING_EDGE;
  else
    usw0 = FALLING_EDGE;
  CISR &= ~(1 << USW0);                      /* clear interrupt flag                      */
}
__declspec (interrupt) void Usw1_Isr (void)
{
  if (DIORead(USW1))
    usw1 = RISING_EDGE;
  else
    usw1 = FALLING_EDGE;
  CISR &= ~(1 << USW1);                      /* clear interrupt flag                      */
}
__declspec (interrupt) void Usw2_Isr (void)
{
  if (DIORead(USW2))
    usw2 = RISING_EDGE;
  else
    usw2 = FALLING_EDGE;
  CISR &= ~(1 << USW2);                      /* clear interrupt flag                      */
}
__declspec (interrupt) void Usw3_Isr (void)
{
  if (DIORead(USW3))
    usw3 = RISING_EDGE;
  else
    usw3 = FALLING_EDGE;
  CISR &= ~(1 << USW3);                      /* clear interrupt flag                      */
}


void Wait4Usw0RisingEdge (void)
{
  while(1)
  {
    if (usw0 == RISING_EDGE)
    {
      usw0 = NO_EDGE;
      ctr = 0;
      DisplayClrTextRow(8);
      return;
    }
    else
    {
      OSTimeDly(2);
    }
  }
}

void Wait4Usw1RisingEdge (void)
{
  while(1)
  {
    if (usw1 == RISING_EDGE)
    {
      usw1 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw2RisingEdge (void)
{
  while(1)
  {
    if (usw2 == RISING_EDGE)
    {
      usw2 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw3RisingEdge (void)
{
  while(1)
  {
    if (usw3 == RISING_EDGE)
    {
      usw3 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw0FallingEdge (void)
{
  while(1)
  {
    if (usw0 == FALLING_EDGE)
    {
      usw0 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw1FallingEdge (void)
{
  while(1)
  {
    if (usw1 == FALLING_EDGE)
    {
      usw1 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw2FallingEdge (void)
{
  while(1)
  {
    if (usw2 == FALLING_EDGE)
    {
      usw2 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}

void Wait4Usw3FallingEdge (void)
{
  while(1)
  {
    if (usw3 == FALLING_EDGE)
    {
      usw3 = NO_EDGE;
      return;
    }
    else
      OSTimeDly(2);
  }
}