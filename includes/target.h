/********************************************************************************************
  MEGA332 und MIO Definitions

  File        : target.h
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 07.08.2003
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Dieses File ermöglicht hardwarenahes programmieren mit C.
********************************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H

#define PADDING 1

#include "mc68332.h"

#define RTC_PADDING     1
#include "rtc72421.h"

#define MC68681_PADDING 1 
#include "mc68681.h"

#define KILO    * (1024     )
#define MEGA    * (1024 KILO)
#define GIGA    * (1024 MEGA)

#define TARGET_NAME     "mega332"

#define RAM_BASE        ( 0x000000L )
#define RAM_TOTAL       ( 1 MEGA + 256 KILO )
#define RAM_MAXSIZE     ( 1 MEGA )
#define RAM_MINSIZE     ( 1 MEGA )
#define RAM_WAIT        ( 0 ) 
#define RAM             ( *(unsigned char(*)[RAM_MAXSIZE])RAM_BASE )

#define ROM_BASE        ( 0x200000L )
#define ROM_MAXSIZE     ( 1 MEGA )
#define ROM_MINSIZE     ( 64 KILO )
#define ROM_WAIT        ( 0 )
#define ROM             ( *(const unsigned char(*)[ROM_MAXSIZE])ROM_BASE )

#define MC68681_BASE    ( 0x300000 )
#define MC68681_SIZE    ( sizeof(struct mc68681) )
#define MC68681         ( *(struct mc68681 *)MC68681_BASE )

#define ONBOARD_IO_BASE ( 0x310000L )
#define ONBOARD_IO_WAIT ( 3 )

#define RTC_BASE        ONBOARD_IO_BASE        
#define RTC_SIZE        ( sizeof(struct rtc72421) )
#define RTC             ( *(struct rtc72421 *)RTC_BASE )

#define CAN_ALE         (*(volatile unsigned char(*))(ONBOARD_IO_BASE + 0x301L))
#define CAN_DATA        (*(volatile unsigned char(*))(ONBOARD_IO_BASE + 0x201L))

#define TLX_BASE        ( 0xe00000L )
#define TLX_SIZE        ( 1 MEGA )
#define TLX_WAIT        ( 3 )
#define TLX             ( (void *)(TLX_BASE) )
#define TLX_0           ( (void *)(TLX_BASE | 0xfffc0) )
#define TLX_1           ( (void *)(TLX_BASE | 0xfffa0) )
#define TLX_2           ( (void *)(TLX_BASE | 0xfff60) )
#define TLX_3           ( (void *)(TLX_BASE | 0xffee0) )

#define ERROR_PORT      ( *(volatile unsigned char *)TLX_0)

/*
 * used vectors
 */
#define VEC_AUTO3   27
#define VEC_AUTO4   28
#define VEC_AUTO5   29
#define VEC_PIT     64
#define VEC_MC68681 VEC_AUTO4
#define VEC_SCI     66
#define VEC_SPI     (VEC_SCI + 1)
#define VEC_TPU     80

#define VEC_TRAP_0     32
#define VEC_TRAP_1     33
#define VEC_TRAP_2     34
#define VEC_TRAP_3     35
#define VEC_TRAP_4     36
#define VEC_TRAP_5     37
#define VEC_TRAP_6     38
#define VEC_TRAP_7     39
#define VEC_TRAP_8     40
#define VEC_TRAP_9     41
#define VEC_TRAP_10    42
#define VEC_TRAP_11    43
#define VEC_TRAP_12    44
#define VEC_TRAP_13    45
#define VEC_TRAP_14    46
#define VEC_TRAP_15    47


/*
 * arbitration number for interrupt sources
 */
#define ARB_SIM    0xc
#define ARB_QSM    0x8
#define ARB_TPU    0x4

/*
 * other defines
 */
#define TRUE  1
#define FALSE  0
#define INPUT   0
#define OUTPUT  1

/*
 * MIO spezifische Makros
 */
#define DISPLAY   (*(volatile unsigned char*) 0xee0000)
#define BEEPER    (*(volatile unsigned char*) 0xee0010)
#define SCHALTER  (*(volatile unsigned char*) 0xee0020)
#define ANZEIGE   (*(volatile unsigned char*) 0xee0040)

#define USW0        TPU_CH_9
#define USW1        TPU_CH_10
#define USW2        TPU_CH_11
#define USW3        TPU_CH_12

#define ENC_SWITCH  TPU_CH_13
#define ENC_A       TPU_CH_14
#define ENC_B       TPU_CH_15

#endif /* #ifndef __TARGET_H */