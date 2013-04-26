/********************************************************************************************
  Standard Register für die DUART MC68681 von Motorola

  File        : mc68681.h
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 28.5.2003
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Dieses File unterstützt die hardwarenahe Programmierung des MC68681 in C
********************************************************************************************/

#ifndef __MC68681_H
#define __MC68681_H

#define _(x) unsigned char _pad_ ## x [MC68681_PADDING]; volatile unsigned char (x);

typedef struct mc68681 {
  _(MRA)
  _(CSRA)
  _(CRA)
  _(TBA)
  _(ACR)
  _(IER)
  _(CTUR)
  _(CTLR)
  _(MRB)
  _(CSRB)
  _(CRB)
  _(TBB)
  _(IVR)
  _(OPCR)
  _(SET)
  _(RESET)
} mc68681;
#undef _

/********************************************************************************************
* STANDARD BITS
********************************************************************************************/

#define BIT0                (0x0001)
#define BIT1                (0x0002)
#define BIT2                (0x0004)
#define BIT3                (0x0008)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)
#define BIT8                (0x0100)
#define BIT9                (0x0200)
#define BITA                (0x0400)
#define BITB                (0x0800)
#define BITC                (0x1000)
#define BITD                (0x2000)
#define BITE                (0x4000)
#define BITF                (0x8000)

/********************************************************************************************
* SPECIAL FUNCTION REGISTER ADDRESSES + CONTROL BITS
********************************************************************************************/

/************************************************************
* MR1A, MR1B
************************************************************/
#define FIVE_BITS_PER_CHAR    (0x00)
#define SIX_BITS_PER_CHAR     (0x01)
#define SEVEN_BITS_PER_CHAR   (0x02)
#define EIGHT_BITS_PER_CHAR   (0x03)
#define EVEN_PARITY           (0x00)
#define ODD_PARITY            (0x04)
#define WITH_PARITY           (0x00)
#define FORCE_PARITY          (0x80)
#define NO_PARITY             (0x10)
#define MULTI_DROP_MODE       (0x18)
#define CHAR_ERROR_MODE       (0x00)
#define BLOCK_ERROR_MODE      (0x20)
#define RX_INT_SELECT_RXRDY   (0x00)
#define RX_INT_SELECT_FFULL   (0x40)
#define RX_RTS_CONTROL_NO     (0x00)
#define RX_RTS_CONTROL_YES    (0x80)

/************************************************************
* MR2A, MR2B
************************************************************/
#define STOP_BIT_1            (0x07)
#define STOP_BIT_15           (0x08)
#define STOP_BIT_2            (0x0f)

/************************************************************
* CSRA, CSRB
************************************************************/
#define BAUDRATE_50           (0x00)
#define BAUDRATE_75           (0x00)
#define BAUDRATE_110          (0x01)
#define BAUDRATE_134_5        (0x02)
#define BAUDRATE_150          (0x03)
#define BAUDRATE_200          (0x03)
#define BAUDRATE_300          (0x04)
#define BAUDRATE_600          (0x05)
#define BAUDRATE_1200         (0x06)
#define BAUDRATE_1050         (0x07)
#define BAUDRATE_2000         (0x07)
#define BAUDRATE_2400         (0x08)
#define BAUDRATE_4800         (0x09)
#define BAUDRATE_7200         (0x0a)
#define BAUDRATE_1800         (0x0a)
#define BAUDRATE_9600         (0x0b)
#define BAUDRATE_19200        (0x0c)
#define BAUDRATE_38400        (0x0c)

/************************************************************
* CRA, CRB
************************************************************/
#define EN_RX                 (0x01)
#define DIS_RX                (0x02)
#define EN_TX                 (0x04)
#define DIS_TX                (0x08)
#define NO_COMMAND            (0x00)
#define RST_MR_PTR            (0x10)
#define RST_RX                (0x20)
#define RST_TX                (0x30)
#define RST_ERR_STAT          (0x40)
#define RST_CHG_INT           (0x50)
#define START_BREAK           (0x60)
#define STOP_BREAK            (0x70)

/************************************************************
* SRA, SRB
************************************************************/
#define RX_READY              (0x01)
#define RX_FFULL              (0x02)
#define TX_READY              (0x04)
#define TX_EMPTY              (0x08)
#define OVERRUN_ERROR         (0x10)
#define PARITY_ERROR          (0x20)
#define FRAMING_ERROR         (0x40)
#define RECEIVED_BREAK        (0x80)

/************************************************************
* IMR (IER)
************************************************************/
#define TX_INT_FLAG_A         (0x01)
#define RX_INT_FLAG_A         (0x02)
#define TX_INT_FLAG_B         (0x10)
#define RX_INT_FLAG_B         (0x20)

#endif /* #ifndef __MC68681_H */