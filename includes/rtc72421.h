/********************************************************************************************
  Standard Register für Real Time Clock RTC72421

  File        : rtc72421.h
  Author      : Rudolf Brunner rudolf.brunner@gmx.ch
  Date        : 28.5.2003
  Last Update : 07.08.2003 Rudolf Brunner rudolf.brunner@gmx.ch
  Target      : MEGA332, MetroTRK and CodeWarrior
  
  Beschreibung: Dieses File unterstützt die hardwarenahe Programmierung des RTC72421 in C
********************************************************************************************/

#ifndef __RTC72421_H
#define __RTC72421_H

#define _(x) unsigned char _pad_ ## x [RTC_PADDING];  volatile unsigned char (x);

typedef struct rtc72421 {
	_(SEC)
	_(SECD)
	_(MIN)
	_(MIND)
	_(HOUR)
	_(HOURD)
	_(DAY)
	_(DAYD)
	_(MON)
	_(MOND)
	_(YEAR)
	_(YEARD)
	_(WEEK)
	_(CTLD)
	_(CTLE)
	_(CTLF)
} rtc72421;

typedef struct rtc72421buf {
	unsigned char sec;
	unsigned char secd;
	unsigned char min;
	unsigned char mind;
	unsigned char hour;
	unsigned char hourd;
	unsigned char day;
	unsigned char dayd;
	unsigned char mon;
	unsigned char mond;
	unsigned char year;
	unsigned char yeard;
	unsigned char week;
} rtc72421buf;

#undef _

#endif /* #ifndef __RTC72421_H */