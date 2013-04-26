/********************************************************************************************

	Display-Driver for MIO with MEGA332 (MC68332)

	File        :	displayNeu.c
	Author      :	Rudolf Brunner rudolf.brunner@gmx.ch
	Date        : 14.10.04
	Target      : MC68332
	
  Beschreibung: Dies ist ein Treiber für das Display auf dem MIO-Board und implementiert die
  wesentlichen Funktion um das Display anzusprechen.
  
  Das RAM des Displays wird in drei virtuelle Displays aufgeteilt. Das entsprechende 
  virtuelle Display kann über DisplaySetLayer(x) festgelegt werden.
  
  Aufteilung des Display-RAMs (8kByte von 64kByte bestückt)
  
              VD0                          VD1                        VD2
  0x0000 +------------+     0x0a80  +------------+     0x1500  +------------+
         | text area  |             | text area  |             | text area  |
         |            |             |            |             |            |
  0x01ff +------------+     0x0c7f  +------------+     0x16ff  +------------+
  0x0200 |  graphics  |     0x0c80  |  graphics  |     0x1700  |  graphics  |
         |    area    |             |    area    |             |    area    |
  0x0a7f +------------+     0x14ff  +------------+     0x1f7f  +------------+
  
********************************************************************************************/

/********************************************************************************************
	Includes & Defines
********************************************************************************************/

#include "MC68332.h"
#include "displayNeu.h"
#include <stdlib.h>


/** Peripheral library standard scalar typedefs
*/

#define LCDEXP      5
#define DEBUG(x)  printf("%d\n",x)

#define Wait4LCD_ErrorExitSta2(x)   for (loop=LCDEXP; (LCDC.status.sta2 != 1) && (loop > 0);loop--) \
	                                if(!loop)   return(x);
#define Wait4LCD_ErrorExitSta3(x)   for (loop=LCDEXP; (LCDC.status.sta3 != 1) && (loop > 0);loop--) \
	                                if(!loop)   return(x);
#define Wait4LCD_ErrorExitSta01(x)   for (loop=LCDEXP; (LCDC.status.sta0 != 1) && (LCDC.status.sta1 != 1) && (loop > 0);loop--) \
	                                if(!loop)   return(x);
	                                
	                                  



/** Adressbereich des Displays
*/
#define DISPLAY_DATA 		0x0ee0000
#define DISPLAY_COMMAND		0x0ee0002
#define LCDD (*(volatile unsigned char*) DISPLAY_DATA)
#define LCDC (*(volatile t_display*) DISPLAY_COMMAND)

 /** Grösse des Text- und Grafikbereichs (Zeile!)
*/
#define TEXTBEREICH          0x001B
#define GRAFIKBEREICH        0x001B
#define DISPLAY_SIZE         GRAFIKBEREICH * 80
#define NOF_ZEILE            10
#define GRAFIK_X             160
#define GRAFIK_Y             80

/** Startadresse der Text- und Grafikbereiche
*/
  #define TEXTSTARTADRESSE0	  0x0000
  #define GRAFIKSTARTADRESSE0	0x0200

  #define TEXTSTARTADRESSE1	  0x0a80
  #define GRAFIKSTARTADRESSE1	0x0c80

  #define TEXTSTARTADRESSE2	  0x1500
  #define GRAFIKSTARTADRESSE2	0x1700
  
  #define CGADRESSE			      0x0002
  #define ADRESSZEIGER        0x0000
  #define CURSORZEIGER        0x0000

/********************************************************************************************
* 
*	COMMAND DEFINITIONS
*
*********************************************************************************************
*/

/** Register settings 
*/
#define SET_CURSOR_POINTER          0x21
#define SET_OFFSET_REGISTER         0x22
#define SET_ADDRESS_POINTER         0x24

/** Register control word 
*/
#define SET_TEXT_HOME_ADDRESS       0x40
#define SET_TEXT_AREA               0x41
#define SET_GRAPHIC_HOME_ADDRESS    0x42
#define SET_GRAPHIC_AREA            0x43

/** Mode set 
*/
#define OR_MODE                     0x80
#define EXOR_MODE                   0x81
#define AND_MODE                    0x83
#define TEXT_ATTRIBUTE_MODE         0x84
#define INTERNAL_CG_ROM_MODE        0x80
#define EXTERNAL_CG_RAM_MODE        0x88

/** Display mode 
*/
#define DISPLAY_OFF                 0x90
#define CURSOR_ON_BLINK_OFF         0x92
#define CURSOR_ON_BLINK_ON          0x93
#define TEXT_ON_GRAPHIC_OFF         0x94
#define	TEXT_OFF_GRAPHIC_ON         0x98
#define TEXT_ON_GRAPHIC_ON          0x9C
			
/** Cursor pattern select
*/
#define ONE_LINE_CURSOR             0xA0
#define TWO_LINE_CURSOR             0xA1
#define THREE_LINE_CURSOR           0xA2
#define FOUR_LINE_CURSOR            0xA3
#define FIVE_LINE_CURSOR            0xA4
#define SIX_LINE_CURSOR             0xA5
#define SEVEN_LINE_CURSOR           0xA6
#define EIGHT_LINE_CURSOR           0xA7

/** Data auto read/write 
*/
#define SET_DATA_AUTO_WRITE         0xB0
#define SET_DATA_AUTO_READ          0xB1
#define AUTO_RESET                  0xB2

/** data read/write 
*/
#define DATA_WRITE_AND_INC          0xC0
#define DATA_READ_AND_INC           0xC1
#define DATA_WRITE_AND_DEC          0xC2
#define DATA_READ_AND_DEC           0xC3
#define DATA_WRITE_AND_NON          0xC4
#define DATA_READ_AND_NON           0xC5

/** Screen peek 
*/
#define SCREEN_PEEK	                0xD0

/** Screen copy 
*/
#define SCREEN_COPY                 0xD8

/** Bit set /reset 
*/
#define BIT_RESET                   0xF0
#define BIT_SET                     0xF8
#define BIT_1                       0xF0
#define BIT_2                       0xF1
#define BIT_3				            		0xF2
#define BIT_4           						0xF3
#define BIT_5           						0xF4
#define BIT_6						            0xF5
#define BIT_7           						0xF6

/********************************************************************************************
* 
*	STATUS WORD REGISTER
*
*********************************************************************************************
*/
typedef struct
{
    /** sta7:	Check blink condition
     *  		0: Disable, 1: Enable
     *
     *	sta6	Error flag. Used for Screen Peek and Screen copy commands
     *
     *		 	0: Disable, 1: Enable
     *	sta5	Check controller operation capability
     *
     *			0: Disable, 1: Enable
     *	sta4	Not used!
     *
     *	sta3	Check Auto mode data write capability
     *			0: Disable, 1: Enable
     *
     *	sta2	Check Auto mode data read capability
     *			0: Disable, 1: Enable
     *
     *	sta1	Check data read/write capability
     *			0: Disable, 1: Enable
     *
     *	sta0	Check command execution capability
     *			0: Disable, 1: Enable
     */	
	unsigned sta7		:1;
	unsigned sta6		:1;
	unsigned sta5		:1;			
	unsigned sta4		:1;		
	unsigned sta3		:1;		
	unsigned sta2		:1;
	unsigned sta1		:1;	
	unsigned sta0		:1;
}t_statusCheck;

/********************************************************************************************
*
*	CHECK COMMAND/DATA READ/WRITE 
*
*********************************************************************************************
*/
typedef union					
{
	/** command	Command for display
	*	status	Check Register
	*/
	unsigned char command;
	t_statusCheck status;
}t_display;


static int loop;
static int cursorRow = 0, cursorCol = 0;
int graphicStartAddr = 0;
int textStartAddr = 0;

int DisplayDoCommand(int command, int data);


/********************************************************************************************
	Functions
********************************************************************************************/

/***************************************************************************
	int DisplayDoCommand (int command, int data)
	  Führt ein DisplayCommando aus
***************************************************************************/
int DisplayDoCommand(int command, int data)
{
  Wait4LCD_ErrorExitSta01(1);               /* Daten übermitteln */
	LCDD = data;
  Wait4LCD_ErrorExitSta01(2);
 	LCDD = data >> 8;
  Wait4LCD_ErrorExitSta01(3);               /* Commando übermitteln */
	LCDC.command = command;
  
  return 0;
}

/***************************************************************************
	int DisplayInit(void)
	  Initialisiert das Display
***************************************************************************/
int DisplayInit (void)
{
	int i;
	graphicStartAddr = GRAFIKSTARTADRESSE0;
	textStartAddr = TEXTSTARTADRESSE0;

  DisplayDoCommand(SET_TEXT_AREA, TEXTBEREICH);
  DisplayDoCommand(SET_GRAPHIC_AREA, GRAFIKBEREICH);
  DisplayDoCommand(SET_TEXT_HOME_ADDRESS, textStartAddr);
  DisplayDoCommand(SET_GRAPHIC_HOME_ADDRESS, graphicStartAddr);
  DisplayDoCommand(SET_ADDRESS_POINTER, ADRESSZEIGER);
  DisplayDoCommand(SET_CURSOR_POINTER, CURSORZEIGER);
  DisplayDoCommand(SET_OFFSET_REGISTER, CGADRESSE);
  DisplayDoCommand(EXOR_MODE, 0);
  DisplayDoCommand(TEXT_ON_GRAPHIC_ON, 0);
  DisplayDoCommand(SET_DATA_AUTO_WRITE, 0);
	
	for (i = 0; i < 0x2000; i++)          /* Clear RAM                      */
	{
    Wait4LCD_ErrorExitSta3(25);
		LCDD = 0x00;
	}

  DisplayDoCommand(AUTO_RESET, 0);
  
  // clear the display
  DisplayClrText();

	return 0;
}

/***************************************************************************
	int DisplayPutChar(int c)
	  dient für eine Printf-Funktion, um ein Zeichen auf dem Display an
	  der aktuellen CursorPosition auszugeben
***************************************************************************/
int DisplayPutChar (char c)
{
  int i, end, cc = 0; // cc = character counter
  
  if ((cursorCol >= TEXTBEREICH - 1) || (c == '\n'))
  {
    cursorRow++;
    cursorCol = 0;
  }
  if (cursorRow == 10)
  {
    DisplayShift();
    cursorRow = 9;
  }
	if (cursorCol == (TEXTBEREICH - 2))
  	DisplaySetCursor(0, cursorRow+1);
  else if (cursorCol == 0 && c == '\n')
    DisplaySetCursor(cursorCol, cursorRow);
  else
    DisplaySetCursor(cursorCol+1, cursorRow);
  if (c != '\n' && c != '\r' && c != '\0' && c != '\t')
  {
    cc += DisplayWriteChar((char)c, cursorRow, cursorCol++);
  }
  if (c == '\t')
  {
    end = 4 - (cursorCol % 4);
    for (i = end; i > 0; i--)
      cc += DisplayWriteChar(' ', cursorRow, cursorCol++);
  }
  return cc;
}

/***************************************************************************
	int DisplayShift(void)
	  Dient der DisplayPutChar-Funktion dazu, den gesamten Inhalt des Displays
	  um eine Zeile nach oben zu schieben
***************************************************************************/
int DisplayShift (void)
{
  int i, err = 0;
  char s[TEXTBEREICH];
  for (i = 0; i <= 8; i++)
  {
    err |= DisplayReadText(&s[0], TEXTBEREICH - 1, i + 1, 1);
    s[26] = '\0';
    err |= DisplayWriteText(&s[0], i, 0);
  }
  err |= DisplayClrTextRow(9);
  return err;
}

/***************************************************************************
	int DisplayReadText(char* text, int laenge, int zeile, int spalte)
	  liest Text der Länge laenge ab der Zeile zeile und Spalte spalte aus
***************************************************************************/
int DisplayReadText (char* text, int laenge, int zeile, int spalte)
{
	int i,adresse;	/* Laufindex */
	
	adresse = textStartAddr + TEXTBEREICH*zeile + spalte -1;

	if (laenge + spalte > TEXTBEREICH)
	  return 31;
	
	/* Adresszeiger setzen */
  DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  DisplayDoCommand(SET_DATA_AUTO_READ, 0);

	/* schreiben... */ 
	for (i = 0; i < laenge; i++)
	{
    Wait4LCD_ErrorExitSta2(36);
		text[i] = LCDD + 0x20;        /* Zu ASCII-Zeichen umwandeln */
	}

  DisplayDoCommand(AUTO_RESET, 0);

	text[++i] = '\0';               /* String abschliessen */
	
	return 0;
}

/***************************************************************************
  int DisplayWriteChar(char c, int zeile, int spalte)
	  Schreibt ein einzelnes Zeichen c an die Zeilen-Spalten-Koordinaten
	  zeile / spalte
***************************************************************************/
int DisplayWriteChar (char c, int zeile, int spalte)
{
	int adresse;	/* Adresse im RAM */
		
  adresse = textStartAddr + zeile * TEXTBEREICH + spalte;
	
	if ((spalte > TEXTBEREICH) || (zeile > NOF_ZEILE - 1))
	  return 41;

	/* Adresszeiger setzen */
  DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  DisplayDoCommand(SET_DATA_AUTO_WRITE, 0);
	
	/* schreiben... */ 
  Wait4LCD_ErrorExitSta3(46);
  LCDD = c-32;

  DisplayDoCommand(AUTO_RESET, 0);
	
	return 1;
}

/***************************************************************************
  int DisplayWriteText(char* text,int zeile,int spalte)
	  Gibt einen Text auf das Display an der Position zeile, spalte aus
***************************************************************************/
int DisplayWriteText (char* text, int zeile, int spalte)
{
	int i, adresse;	/* Laufindex */
	char *pChar = text;
  int laenge = 0;
  
	while (*pChar++)  /* Laenge bestimmen */
	  laenge++;

  adresse = textStartAddr + zeile * TEXTBEREICH + spalte;

  if ((zeile >= NOF_ZEILE) || (spalte + laenge > TEXTBEREICH))
    return 41;
    	
	/* Adresszeiger setzen */
  DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  DisplayDoCommand(SET_DATA_AUTO_WRITE, 0);
	
	/* schreiben... */ 
	for (i = 0; i < laenge; i++)
	{
    Wait4LCD_ErrorExitSta3(45);
		LCDD = text[i] - 0x20;          /* ASCII zu Display-Zeichen wandeln */
	}

  DisplayDoCommand(AUTO_RESET, 0);
	
	return 0;
}

/***************************************************************************
  int DisplayClrTextRow (int zeile)
	  Loescht eine Zeile auf dem Display
***************************************************************************/
int DisplayClrTextRow (int zeile)
{
	int i = 0;	/* Laufindex */
	int adresse;
	
  adresse = textStartAddr + zeile * TEXTBEREICH;
	
	if (zeile >= NOF_ZEILE)
	  return 51;
	
	/* Adresszeiger setzen */
  DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  DisplayDoCommand(SET_DATA_AUTO_WRITE, 0);
	
	/* schreiben... */ 
	for (i = 0; i < TEXTBEREICH; i++)
	{
    Wait4LCD_ErrorExitSta3(56);
		LCDD = 0x00;
	}

  DisplayDoCommand(AUTO_RESET, 0);

	return 0;	
}

/***************************************************************************
  int DisplayClrText(void)
	  Löscht den gesamten Text des Displays
***************************************************************************/
int DisplayClrText (void)
{
	int i, adresse;	/* Laufindex */

  cursorCol = cursorRow = 0;
  adresse = textStartAddr;
	
	/* Adresszeiger setzen */
  DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  DisplayDoCommand(SET_DATA_AUTO_WRITE, 0);
	
	/* schreiben... */ 
	for (i = 0; i < TEXTBEREICH * NOF_ZEILE; i++)
	{
    Wait4LCD_ErrorExitSta3(65);
		LCDD = 0x00;
	}

  DisplayDoCommand(AUTO_RESET, 0);

  return 0;
}

/***************************************************************************
  int DisplayShowLayer (int layer)
	  Setzt den Grafikpointer auf den akutellen Layer
***************************************************************************/
int DisplaySetLayer (int layer)
{
  if (layer == 0)
  {
    textStartAddr = TEXTSTARTADRESSE0;
    graphicStartAddr = GRAFIKSTARTADRESSE0;
  }
  else if (layer == 1)
  {
    textStartAddr = TEXTSTARTADRESSE1;
    graphicStartAddr = GRAFIKSTARTADRESSE1;
  }
  else
  {
    textStartAddr = TEXTSTARTADRESSE2;
    graphicStartAddr = GRAFIKSTARTADRESSE2;
  }
  DisplayDoCommand(SET_TEXT_HOME_ADDRESS, textStartAddr);
  DisplayDoCommand(SET_GRAPHIC_HOME_ADDRESS, graphicStartAddr);
  
  return 0;
}

/***************************************************************************
  int DisplaySetCursor (int zeile, int spalte)
	  Setzt den Cursor an die entsprechende Position
***************************************************************************/
int DisplaySetCursor (int zeile, int spalte)
{
  DisplayDoCommand(SET_CURSOR_POINTER, spalte + (zeile << 8));
  DisplayDoCommand(ONE_LINE_CURSOR, 0);
  DisplayDoCommand(CURSOR_ON_BLINK_ON | TEXT_ON_GRAPHIC_ON, 0);

	return 0;
}

/***************************************************************************
  int DisplayRemoveCursor (void)
	  schaltet den Cursor aus
***************************************************************************/
int DisplayRemoveCursor (void)
{
  DisplayDoCommand(TEXT_ON_GRAPHIC_ON, 0);

  return 0;
}

/***************************************************************************
  int DisplayClrPoint (int x, int y)
	  Löscht einen Punkt an der x/y Koordinate
***************************************************************************/
int DisplayClrPoint (int x, int y)
{
	int bytenr, bit, adresse;

	if( ((x >= 0) && (x < GRAFIK_X)) && ((y >= 0) && (y < GRAFIK_Y)) )
	{
		bytenr = (GRAFIK_Y - 1 - y) * TEXTBEREICH + (x / 6);
	  	adresse = graphicStartAddr + bytenr;
		bit = x % 6;

  		DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  		DisplayDoCommand(BIT_RESET + (-(bit-5) & 0x07), 0);
  	}
  return 0;
}

/***************************************************************************
  int DisplaySetPoint (int x, int y)
	  Setzt einen Punkt an der x/y Koordinate
***************************************************************************/
int DisplaySetPoint (int x, int y)
{
	int bytenr, bit, adresse;
	
	if( ((x >= 0) && (x < GRAFIK_X)) && ((y >= 0) && (y < GRAFIK_Y)) )
	{
		bytenr = (GRAFIK_Y - 1 - y) * TEXTBEREICH + (x / 6);
  		adresse = graphicStartAddr + bytenr;
		bit = x % 6;

  		DisplayDoCommand(SET_ADDRESS_POINTER, adresse);
  		DisplayDoCommand(BIT_SET + (-(bit-5) & 0x07), 0);
  	}
  return 0;
}

/***************************************************************************
  void DisplayClrLine (int x_start, int y_start, int x_end, int y_end)
	  Löscht eine Linie
***************************************************************************/
void DisplayClrLine (int x_start, int y_start, int x_end, int y_end)
{
	int x, y, temp, delta, delta_x, delta_y;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	
	if (delta_x == 0)
		for (y = 0; y <= (y_end-y_start); y++)
			DisplayClrPoint(x_start, y+y_start);
	else if (delta_y == 0)
		for(x = 0; x <= (delta_x); x++)
			DisplayClrPoint(x + x_start, y_start);
	else if (delta_y / delta_x)  //ist Steigung > 1
	{
		if (y_end < y_start)
		{
			temp = y_end;
			y_end = y_start;
			y_start = temp;
			temp = x_end;
			x_end = x_start;
			x_start = temp;
		}
		for (y = 0; y <= (delta_y); y++)
		{
			x = x_start + y * (x_end - x_start) / (delta_y);
			DisplayClrPoint(x, y_start + y);
		}
	}
	else          // ist Steigung < 1
	{
		if (x_end < x_start)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;		
	  }
		for (x = 0; x <= (delta_x); x++)
		{
			y = y_start + x * (y_end - y_start) / (delta_x);
			DisplayClrPoint(x_start + x, y);
		}
	}
}

/***************************************************************************
  void DisplayDrawLine(int x_start, int y_start, int x_end, int y_end)
	  Zeichnet eine Linie
***************************************************************************/
void DisplayDrawLine (int x_start, int y_start, int x_end, int y_end)
{
	int x, y, temp, delta, delta_x, delta_y;

	delta_x = abs(x_end - x_start);
	delta_y = abs(y_end - y_start);
	
	if (delta_x == 0)
		for (y = 0; y <= (y_end-y_start); y++)
			DisplaySetPoint(x_start, y+y_start);
	else if (delta_y == 0)
		for(x = 0; x <= (delta_x); x++)
			DisplaySetPoint(x+x_start, y_start);
	else if (delta_y / delta_x)  //ist Steigung > 1
	{
		if (y_end < y_start)
		{
			temp = y_end;
			y_end = y_start;
			y_start = temp;
			temp = x_end;
			x_end = x_start;
			x_start = temp;
		}
		for(y = 0; y <= (delta_y); y++)
		{
			x = x_start + y * (x_end - x_start) / (delta_y);
			DisplaySetPoint(x, y_start + y);
		}
	}
	else    // ist Steigung < 1
  {
		if (x_end < x_start)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;
		}
		for (x = 0; x <= (delta_x); x++)
		{
			y = y_start + x * (y_end - y_start) / (delta_x);
			DisplaySetPoint(x_start + x, y);
		}
	}
}

/***************************************************************************
  void DisplayClrRect (int x1, int y1, int x2, int y2)
	  Löscht ein Rechteck: Angabe linke untere Ecke und rechte obere Ecke
***************************************************************************/
void DisplayClrRect (int x1, int y1, int x2, int y2)
{
	DisplayClrLine(x1, y1, x1, y2);
	DisplayClrLine(x1, y1, x2, y1);
	DisplayClrLine(x2, y1, x2, y2);
	DisplayClrLine(x1, y2, x2, y2);
}

/***************************************************************************
  void DisplayDrawRect (int x1, int y1, int x2, int y2)
	  Zeichnet ein Rechteck: Angabe linke untere Ecke und rechte obere Ecke
***************************************************************************/
void DisplayDrawRect (int x1, int y1, int x2, int y2)
{
	DisplayDrawLine(x1, y1, x1, y2);
	DisplayDrawLine(x1, y1, x2, y1);
	DisplayDrawLine(x2, y1, x2, y2);
	DisplayDrawLine(x1, y2, x2, y2);
}

/***************************************************************************
  void DisplayClrArea (int x_start, int y_start, int x_end, int y_end)
	  Löscht eine Fläche: Angabe linke untere Ecke und rechte obere Ecke
***************************************************************************/
void DisplayClrArea (int x_start, int y_start, int x_end, int y_end)
{
	int x, y;

	for (x = x_start; x <= x_end; x++)
		for (y = y_start; y <= y_end; y++)
			DisplayClrPoint(x, y);
}

/***************************************************************************
  void DisplayFillArea (int x_start, int y_start, int x_end, int y_end)
	  Zeichnet ein Rechteck: Angabe linke untere Ecke und rechte obere Ecke
***************************************************************************/
void DisplayFillArea (int x_start, int y_start, int x_end, int y_end)
{
	int x, y;
	
	for (x = x_start; x <= x_end; x++)
		for (y = y_start; y <= y_end; y++)
			DisplaySetPoint(x, y);
}

/***************************************************************************
	void DisplayDrawCircle(int x0, int y0, int radius)
	  zeichnet eine Kreislinie um den Mittelpunkt x0/y0 mit Radius radius
***************************************************************************/
 void DisplayDrawCircle(int x0, int y0, int radius)
 {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    DisplaySetPoint(x0, y0 + radius);
    DisplaySetPoint(x0, y0 - radius);
    DisplaySetPoint(x0 + radius, y0);
    DisplaySetPoint(x0 - radius, y0);
 
    while(x < y) 
    {
       if(f >= 0) 
       {
          y--;
          ddF_y += 2;
          f += ddF_y;
       }
      
       x++;
       ddF_x += 2;
       f += ddF_x + 1;
 
       DisplaySetPoint(x0 + x, y0 + y);
       DisplaySetPoint(x0 - x, y0 + y);
       DisplaySetPoint(x0 + x, y0 - y);
       DisplaySetPoint(x0 - x, y0 - y);
       DisplaySetPoint(x0 + y, y0 + x);
       DisplaySetPoint(x0 - y, y0 + x);
       DisplaySetPoint(x0 + y, y0 - x);
       DisplaySetPoint(x0 - y, y0 - x);
    }
 }


/***************************************************************************
	void DisplayClearCircle(int x0, int y0, int radius)
	  Löscht eine Kreislinie um den Mittelpunkt x0/y0 mit Radius radius
***************************************************************************/
 void DisplayClearCircle(int x0, int y0, int radius)
  {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    DisplayClrPoint(x0, y0 + radius);
    DisplayClrPoint(x0, y0 - radius);
    DisplayClrPoint(x0 + radius, y0);
    DisplayClrPoint(x0 - radius, y0);
 
    while(x < y) 
    {
       if(f >= 0) 
       {
          y--;
          ddF_y += 2;
          f += ddF_y;
       }
      
       x++;
       ddF_x += 2;
       f += ddF_x + 1;
 
       DisplayClrPoint(x0 + x, y0 + y);
       DisplayClrPoint(x0 - x, y0 + y);
       DisplayClrPoint(x0 + x, y0 - y);
       DisplayClrPoint(x0 - x, y0 - y);
       DisplayClrPoint(x0 + y, y0 + x);
       DisplayClrPoint(x0 - y, y0 + x);
       DisplayClrPoint(x0 + y, y0 - x);
       DisplayClrPoint(x0 - y, y0 - x);
    }
 }


/***************************************************************************
	void DisplayDrawFullCircle(int x_0, int y_0, int radius)
	  zeichnet einen ausgefüllten Kreis um den Mittelpunkt x0/y0 mit Radius radius
***************************************************************************/
void DisplayDrawFullCircle(int x_0, int y_0, int radius)
{
  int f,ddF_x, ddF_y, x, y;
    
  f = 1 - radius;
  ddF_x = 0;
  ddF_y = -2 * radius;
  x = 0;
  y = radius;  

  DisplayDrawLine(x_0, y_0-radius ,x_0, y_0+radius);

  while(x < y) {
    if(f >= 0) {
      DisplayDrawLine(x_0+y, y_0-x, x_0+y, y_0+x);
      DisplayDrawLine(x_0-y, y_0-x, x_0-y, y_0+x);

      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;

    DisplayDrawLine(x_0+x, y_0-y, x_0+x, y_0+y);
    DisplayDrawLine(x_0-x, y_0-y, x_0-x, y_0+y);
  }
}

/***************************************************************************
	void DisplayClearFullCircle(int x_0, int y_0, int radius)
	  löscht einen ausgefüllten Kreis um den Mittelpunkt x0/y0 mit Radius radius
***************************************************************************/
void DisplayClearFullCircle(int x_0, int y_0, int radius)
{
  int f,ddF_x, ddF_y, x, y;
    
  f = 1 - radius;
  ddF_x = 0;
  ddF_y = -2 * radius;
  x = 0;
  y = radius;  

  DisplayClrLine(x_0, y_0-radius, x_0, y_0+radius);

  while(x < y) {
    if(f >= 0) {
      DisplayClrLine(x_0+y, y_0-x, x_0+y, y_0+x);
      DisplayClrLine(x_0-y, y_0-x, x_0-y, y_0+x);

      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;

    DisplayClrLine(x_0+x, y_0-y, x_0+x, y_0+y);
    DisplayClrLine(x_0-x, y_0-y, x_0-x, y_0+y);
  }
}

