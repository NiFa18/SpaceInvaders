/********************************************************************************************
  Standard Register für den MC68332 von Motorola

  HSR - Hochschule für Technik Rapperswil
  File        : mc68332.h
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 28.05.2003
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
  Target      : MC68332 & CodeWarrior
  
  Beschreibung: Dieses File unterstützt die hardwarenahe Programmierung des MC68332 in C
********************************************************************************************/
#ifndef __MC68332_H
#define __MC68332_H

//usefull makros
#define EXCEPT_VEC(x)  (*(void (**)(void))((x) * 4))
#define ENABLE_CPU_INTERRUPTS asm  {andi   #0xf8ff,sr}
#define DISABLE_CPU_INTERRUPTS asm {ori    #0x700,sr}
#define GET_STATUS_REGISTER(x) asm {move.w sr,d0;\
                                    move.w d0,x;}
#define SET_STATUS_REGISTER(x) asm {move.w x,sr;}
#define GET_STACK_POINTER(x)   asm {move.l sp,d0;\
                                    move.l d0,x;}
#define SET_STACK_POINTER(x)   asm {move.l x,sp;}

#define GET_D0(x) asm   {move.l D0,x}
#define SET_D0(x) asm   {move.l x,D0}
#define GET_D1(x) asm   {move.l D1,x}
#define SET_D1(x) asm   {move.l x,D1}
#define GET_D2(x) asm   {move.l D2,x}
#define SET_D2(x) asm   {move.l x,D2}
#define GET_D3(x) asm   {move.l D3,x}
#define SET_D3(x) asm   {move.l x,D3}
#define GET_D4(x) asm   {move.l D4,x}
#define SET_D4(x) asm   {move.l x,D4}
#define GET_D5(x) asm   {move.l D5,x}
#define SET_D5(x) asm   {move.l x,D5}
#define GET_D6(x) asm   {move.l D6,x}
#define SET_D6(x) asm   {move.l x,D6}
#define GET_D7(x) asm   {move.l D7,x}
#define SET_D7(x) asm   {move.l x,D7}

#define GET_A0(x) asm   {move.l A0,x}
#define SET_A0(x) asm   {move.l x,A0}
#define GET_A1(x) asm   {move.l A1,x}
#define SET_A1(x) asm   {move.l x,A1}
#define GET_A2(x) asm   {move.l A2,x}
#define SET_A2(x) asm   {move.l x,A2}
#define GET_A3(x) asm   {move.l A3,x}
#define SET_A3(x) asm   {move.l x,A3}
#define GET_A4(x) asm   {move.l A4,x}
#define SET_A4(x) asm   {move.l x,A4}
#define GET_A5(x) asm   {move.l A5,x}
#define SET_A5(x) asm   {move.l x,A5}
#define GET_A6(x) asm   {move.l A6,x}
#define SET_A6(x) asm   {move.l x,A6}
#define GET_A7(x) asm   {move.l A7,x}
#define SET_A7(x) asm   {move.l x,A7}



/* MC68332 SIM Peripheral Device Registers Addresses */
#define MC68332_SIM_BASE  0xFFFA00

#define SIMCR    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x00))
#define SIMTR    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x02))
#define SYNCR    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x04))  
#define RSR      (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x07))
#define SIMTRE   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x08))
#define PORTE0   (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x11))
#define PORTE1   (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x13))
#define DDRE     (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x15))
#define PEPAR    (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x17))
#define PORTF0   (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x19))
#define PORTF1   (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x1B))
#define DDRF     (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x1D))
#define PFPAR    (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x1F))
#define SYPCR    (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x21))
#define PICR     (* (volatile unsigned short*) (MC68332_SIM_BASE+0x22))
#define PITR     (* (volatile unsigned short*) (MC68332_SIM_BASE+0x24))
#define SWSR     (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x27))
#define TSTMSRA  (* (volatile unsigned short*) (MC68332_SIM_BASE+0x30))    
#define TSTMSRB  (* (volatile unsigned short*) (MC68332_SIM_BASE+0x32))
#define TSTSC    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x34))
#define TSTRC    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x36))
#define CREG     (* (volatile unsigned short*) (MC68332_SIM_BASE+0x38))
#define DREG     (* (volatile unsigned short*) (MC68332_SIM_BASE+0x3A))
#define PORTC    (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x41))
#define CSPAR0   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x44))
#define CSPAR1   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x46))
#define CSBARBT  (* (volatile unsigned short*) (MC68332_SIM_BASE+0x48))
#define CSORBT   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x4A))
#define CSBAR0   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x4C))
#define CSOR0    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x4E))
#define CSBAR1   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x50))
#define CSOR1    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x52))
#define CSBAR2   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x54))
#define CSOR2    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x56))
#define CSBAR3   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x58))
#define CSOR3    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x5A))
#define CSBAR4   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x5C))
#define CSOR4    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x5E))  
#define CSBAR5   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x60))
#define CSOR5    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x62))
#define CSBAR6   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x64))
#define CSOR6    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x66))
#define CSBAR7   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x68))
#define CSOR7    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x6A))
#define CSBAR8   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x6C))
#define CSOR8    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x6E))
#define CSBAR9   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x70))
#define CSOR9    (* (volatile unsigned short*) (MC68332_SIM_BASE+0x72))
#define CSBAR10  (* (volatile unsigned short*) (MC68332_SIM_BASE+0x74))
#define CSOR10   (* (volatile unsigned short*) (MC68332_SIM_BASE+0x76))

/* MC68332 QSM Peripheral Device Registers Addresses */
#define MC68332_QSM_BASE 0xFFFC00

#define QSMCR    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x00))
#define QTEST    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x02))
#define QILR_VR  (* (volatile unsigned short*) (MC68332_QSM_BASE+0x04))
#define QILR     (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x04))
#define QIVR     (* (volatile unsigned char*)  (MC68332_SIM_BASE+0x05))
#define SCCR0    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x08))
#define SCCR1    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x0A))
#define SCSR     (* (volatile unsigned short*) (MC68332_QSM_BASE+0x0C))
#define SCDR     (* (volatile unsigned short*) (MC68332_QSM_BASE+0x0E))
#define PORTQS   (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x15))
#define PQSPAR   (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x16))
#define DDRQS    (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x17))
#define SPCR0    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x18))
#define SPCR1    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x1A))
#define SPCR2    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x1C))
#define SPCR3    (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x1E))
#define SPSR     (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x1F))
#define RR(X)    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x100+2*X))
#define TR(X)    (* (volatile unsigned short*) (MC68332_QSM_BASE+0x120+2*X))
#define CR(X)    (* (volatile unsigned char*)  (MC68332_QSM_BASE+0x140+X))

/* MC68332 TPU Peripheral Device Registers Addresses */
#define MC68332_TPU_BASE 0xFFFE00

#define TPUMCR   (* (volatile unsigned short*) (MC68332_TPU_BASE+0x00))
#define TCR      (* (volatile unsigned short*) (MC68332_TPU_BASE+0x02))
#define DSCR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x04))
#define DSSR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x06))
#define TICR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x08))
#define CIER     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x0A))
#define CFSR0    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x0C))
#define CFSR1    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x0E))
#define CFSR2    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x10))
#define CFSR3    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x12))
#define HSQR0    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x14))
#define HSQR1    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x16))
#define HSRR0    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x18))
#define HSRR1    (* (volatile unsigned short*) (MC68332_TPU_BASE+0x1A))
#define CPR0     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x1C))
#define CPR1     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x1E))
#define CISR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x20))
#define LR       (* (volatile unsigned short*) (MC68332_TPU_BASE+0x22))
#define SGLR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x24))
#define DCNR     (* (volatile unsigned short*) (MC68332_TPU_BASE+0x26))

#define MC68332_TPURAM_BASE  0xFFFF00  
#define TPU_RAM(CH,PAR)  (* (volatile unsigned short*)(MC68332_TPURAM_BASE+(CH)*0x10+(PAR)*0x02))  

//TPU Channels
#define TPU_CH_0     0
#define TPU_CH_1     1
#define TPU_CH_2     2
#define TPU_CH_3     3
#define TPU_CH_4     4
#define TPU_CH_5     5
#define TPU_CH_6     6
#define TPU_CH_7     7
#define TPU_CH_8     8
#define TPU_CH_9     9
#define TPU_CH_10   10
#define TPU_CH_11   11
#define TPU_CH_12   12
#define TPU_CH_13   13
#define TPU_CH_14   14
#define TPU_CH_15   15

#endif /* ifndef __MC68332_H */