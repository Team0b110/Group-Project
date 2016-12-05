#include <p18f452.h>
#include <delays.h>
#include <p18cxxx.h>
#include "xlcd2.h"

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#define _XTAL_FREQ 20000000UL

void DelayFor18TCY(void)  //delays 20 cycles
 {
    Delay10TCYx(0x6);
    return;
 }

void DelayPORXLCD(void)   // minimum 15ms
 {
    Delay100TCYx(0xF0);   // 100TCY * 160
    return;
 }

void DelayXLCD(void)      // minimum 5ms
 {
    Delay100TCYx(0xF6);      // 100TCY * 54
    return;
 }

/***************************************************************************/
void LCD_init(void)
 {
    PORTD = 0X00;
    TRISD = 0X00;
    OpenXLCD(FOUR_BIT & LINES_5X7);
    while( BusyXLCD() );
    WriteCmdXLCD( SHIFT_DISP_LEFT );
    while( BusyXLCD() );
    WriteCmdXLCD( BLINK_OFF & CURSOR_OFF ); 
    while( BusyXLCD());
 }

char str_toint(int id)
{
    char val;
    if (id == 0)
    {
        val = '0';
    }
    else if (id == 1)
    {
        val = '1';
    }
    else if (id == 2)
    {
        val = '2';
    }
    else if (id == 3)
    {
        val = '3';
    }
    else if (id == 4)
    {
        val = '4';
    }
    else if (id == 5)
    {
        val = '5';
    }
    else if (id == 6)
    {
        val = '6';
    }
    else if (id == 7)
    {
        val = '7';
    }
    else if (id == 8)
    {
        val = '8';
    }
    else if (id == 9)
    {
        val = '9';
    }
    else // should not occur
    {
        val = '0';
    }
    return val;
}

void LCD_printf(int line_num, char * word)
{    
    if (line_num == 1)
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 2)
    {
        SetDDRamAddr(0x40);
        while( BusyXLCD() );
        putsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 3)
    {
        SetDDRamAddr(0x10);
        while( BusyXLCD() );
        putsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 4)
    {
        SetDDRamAddr(0x50);
        while( BusyXLCD() );
        putsXLCD(word);
        while( BusyXLCD() );
    }
    else
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putrsXLCD("ERROR: line #");
        while( BusyXLCD() );
    }
}

void LCD_print(int line_num, rom const char * word)
{    
    if (line_num == 1)
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putrsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 2)
    {
        SetDDRamAddr(0x40);
        while( BusyXLCD() );
        putrsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 3)
    {
        SetDDRamAddr(0x10);
        while( BusyXLCD() );
        putrsXLCD(word);
        while( BusyXLCD() );
    }
    else if (line_num == 4)
    {
        SetDDRamAddr(0x50);
        while( BusyXLCD() );
        putrsXLCD(word);
        while( BusyXLCD() );
    }
    else
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putrsXLCD("ERROR: line #");
        while( BusyXLCD() );
    }
}

int readHeartRate(){
    int heartrate;
    int beats;
    
    
    beats = 0;
    heartrate = 0;
    LATEbits.LATE2 = 1 ;
    LATEbits.LATE2 = 0;

    Delay10KTCYx(400);
    beats = PORTEbits.RE1 | beats;
    beats = beats << 1;
    beats = PORTCbits.RC5 | beats;
    beats = beats << 1;
    beats = PORTCbits.RC4 | beats;
    beats = beats << 1;
    beats = PORTCbits.RC2| beats;
    heartrate = beats * 15;
    Nop();
    Nop();
   /// p = (char *)&heartrate; 
    //LCD_prinf(2,p);
    //num = 10 * num + keypad_keyint(typed[i]);
    
    return heartrate;
    
}

int readIRADC(){
    int i1;
    int input1;
    input1 = 0;
  
    
    
    
    LATCbits.LATC3= 0; 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC3= 1; 
    for(i1 = 0;i1<8;i1++ ){
    input1 = input1<< 1;
    input1 = input1 | PORTCbits.RC0; //adding bit to the end 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    }
    return input1;
}

int readREDADC(){
    int i;
    int input;
    input = 0;
   
    
   
    
    
    LATCbits.LATC3= 0; 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC3= 1; 
 
   
    for(i = 0;i<8;i++ ){
    input = input<< 1;
    input = input | PORTCbits.RC6; //adding bit to the end 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    }
    return input;
}
     
    

void main(void){
    int recieved1;
    int recieved2;
    int  measuredheartrate;
     measuredheartrate = 0;
    recieved2 = 0;
    recieved1 = 0;
    LCD_init();
    TRISEbits.TRISE1 = 1;
    TRISEbits.TRISE2 = 0;
    TRISCbits.RC6 = 1; 
    TRISCbits.RC5 = 1; 
    TRISCbits.RC4 = 1;
    TRISCbits.RC3 = 0;
    TRISCbits.RC2 = 1;
    TRISCbits.RC1 = 0;
    TRISCbits.RC0 = 1;
    
    LCD_print(1,"HR 120 BPM");
    LCD_print(2,"O2SAT 98%");
    LCD_print(3,"GLUCOSE: 75 mg/dL");
    LCD_print(4,"TEMP: 25 C");
    recieved1 = readIRADC();
    recieved2 = readREDADC();
    measuredheartrate = readHeartRate();
    Nop();
    Nop();
   

}



