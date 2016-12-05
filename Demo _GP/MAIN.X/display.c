#include <p18cxxx.h>
#include <portb.h>
#include <delays.h>
#include <string.h>
#include "xlcd2.h"

/* Set configuration bits for use with ICD2 / PICDEM2 PLUS Demo Board: */
#pragma config OSC = HS       // set HS oscillator
#pragma config WDT = OFF      // disable watchdog timer
#pragma config LVP = OFF      // disable low voltage programming
#define _XTAL_FREQ 20000000UL

/****************************************************************************/
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

// IMPORTANT: Run LCD_init(); before running this test
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

// IMPORTANT: Run LCD_init(); before running this test
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

// IMPORTANT: Run LCD_init(); before running this test
void LCD_clrln(int line_num)
 {
    /* 
     * Line1 0x00
     * Line2 0x40
     * Line3 0x10
     * Line4 0x50
     */

    char cl_line[17];
    memset(cl_line, ' ', sizeof(cl_line));
    
    if (line_num == 1)
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
    }
    else if (line_num == 2)
    {
        SetDDRamAddr(0x40);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
    }
    else if (line_num == 3)
    {
        SetDDRamAddr(0x10);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
    }
    else if (line_num == 4)
    {
        SetDDRamAddr(0x50);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
    }
    else
    {
        SetDDRamAddr(0x00);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );

        SetDDRamAddr(0x40);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
        
        SetDDRamAddr(0x10);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );

        SetDDRamAddr(0x50);
        while( BusyXLCD() );
        putsXLCD(cl_line);
        while( BusyXLCD() );
    }

    
 }

/****************************************************************************/
void keypad_init(void)
{
    // configure PORTB <4:0> pins to be inputs
    TRISBbits.TRISB0 = 1; // data available line
    TRISBbits.TRISB1 = 1; // bit 0 (1's)
    TRISBbits.TRISB2 = 1; // bit 1 (2's)
    TRISBbits.TRISB3 = 1; // bit 2 (4's)
    TRISBbits.TRISB4 = 1; // bit 3 (8's)
}

int keypad_keyint(char id)
{
    int val;
    if (id == '0')
    {
        val = 0;
    }
    else if (id == '1')
    {
        val = 1;
    }
    else if (id == '2')
    {
        val = 2;
    }
    else if (id == '3')
    {
        val = 3;
    }
    else if (id == '4')
    {
        val = 4;
    }
    else if (id == '5')
    {
        val = 5;
    }
    else if (id == '6')
    {
        val = 6;
    }
    else if (id == '7')
    {
        val = 7;
    }
    else if (id == '8')
    {
        val = 8;
    }
    else if (id == '9')
    {
        val = 9;
    }
    else // should not occur
    {
        val = 0;
    }
    return val;
}

char keypad_keypress(void)
{
    if (PORTBbits.RB0 == 1) // a key is pressed
    {
        if (PORTBbits.RB4 == 1) // inputs 0b00001xxx
        {
            if (PORTBbits.RB3 == 1) // inputs 0b000011xx
            {
                if (PORTBbits.RB2 == 1) // inputs 0b0000111x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00001111
                    {
                        return 'A';
                    }
                    else // inputs 0b00001110
                    {
                        return 'B';
                    }
                }
                else // inputs 0b0000110x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00001101
                    {
                        return 'C';
                    }
                    else // inputs 0b00001100
                    {
                        return 'D';
                    }
                }
            }
            else // inputs 0b000010xx
            {
                if (PORTBbits.RB2 == 1) // inputs 0b0000101x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00001011
                    {
                        return '3';
                    }
                    else // inputs 0b00001010
                    {
                        return '6';
                    }
                }
                else // inputs 0b0000100x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00001001
                    {
                        return '9';
                    }
                    else // inputs 0b00001000
                    {
                        return 'E';
                    }
                }
            }
        }
        else // inputs 0b00000xxx
        {
            if (PORTBbits.RB3 == 1) // inputs 0b000001xx
            {
                if (PORTBbits.RB2 == 1) // inputs 0b0000011x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00000111
                    {
                        return '2';
                    }
                    else // inputs 0b00000110
                    {
                        return '5';
                    }
                }
                else // inputs 0b0000010x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00000101
                    {
                        return '8';
                    }
                    else // inputs 0b00000100
                    {
                        return 'F';
                    }
                }
            }
            else // inputs 0b000000xx
            {
                if (PORTBbits.RB2 == 1) // inputs 0b0000001x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00000011
                    {
                        return '1';
                    }
                    else // inputs 0b00000010
                    {
                        return '4';
                    }
                }
                else // inputs 0b0000000x
                {
                    if (PORTBbits.RB1 == 1) // inputs 0b00000001
                    {
//                        keypad_keychr('7');
                        return '7';
                    }
                    else // inputs 0b00000000
                    {
                        return '0';
                    }
                }
            }
        }
    }
    else // a key is not pressed
    {
        return '!';
    }
}

/***************************************************************************/
void add_spaces(char *dest, int size, int num_of_spaces)
{
    int len = strlen(dest);
    if( len + num_of_spaces >= size ) 
    {
        num_of_spaces = size - len - 1;
    }  
    memset( dest+len, ' ', num_of_spaces );   
    dest[len + num_of_spaces] = '\0';
}

int int_conv(char * vals)
{
    // vals is an array of character
    // use keypad_keyint to get corresponding integers, put it in temp int array
    int i = 0;
    int num = 0;
    int val;
    int temp[16];
    while(vals[i] != '/0')
    {
        val = keypad_keyint(vals[i]);
        temp[i] = val;
    }
    // use formula to convert
    for (i = 0; i < sizeof(temp); i++)
    {
        num = 10 * num + temp[i];
    }
    
    // return converted decimal integer
    return (num);
}

/***************************************************************************/
void blinkLED(void)
 {
    // LED needs to be connected to any pin on PORTD
    TRISD = 0x00;
    while(1)
    {
        TRISD = 0XFF;
        Delay10KTCYx(10);
        TRISD = 0x00;
        Delay10KTCYx(10);
    }
 }

/***************************************************************************/
 
void main(void)
{   
    // scroll up   - A
    // scroll down - B
    // enter intervals - C
    // enter no. measurements - D
    
    int i;                  //counter var used later
    int num = 0;            //used to calc. the int value of the entered value from the keypad
    int c = 0;              //counter used 
    int meas_val = 0;
    int intv_val = 0;
    char meas[17];          // for specifying # of measurements
    char intv[17];          // for specifying intervals
    char typed[17];         // the active input
    memset(typed, ' ', 15);
    typed[16] = '\0';
    memset(meas, ' ', 15);
    meas[16] = '\0';
    memset(intv, ' ', 15);
    intv[16] = '\0';
    
    LCD_init();
    keypad_init();
    
    while (1)
    {
        char key = keypad_keypress();
        if (key != '!')
        {
            if (c < 16)
            {
                if (key != 'A' || key != 'B' || key != 'C' || key != 'D' || key != 'E')
                {
                    typed[c] = key;
                    Delay10KTCYx(0x20);
                    c++;
                }        
            }
            else
            {
                typed[c] = '\0';
            }
            
            if (key == 'A')
            {
                //scroll up  
            }
            else if (key == 'B')
            {
                //scroll down
                
            }
            else if (key == 'C')
            {
                // clear the old value to display the new
                i = 0;
                memset(intv, ' ', 15);
                intv[16] = '\0';
                // for the display
                while(typed[i] != '\0')
                {
                    if (typed[i] != 'A')
                    {
                        if (typed[i] != 'B')
                        {
                            if (typed[i] != 'C')
                            {
                                if(typed[i] != 'D')
                                {
                                    if (typed[i] != 'E')
                                    {
                                        if (typed[i] != 'F')
                                        {
                                            intv[i] = typed[i];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // for the calculation
                    num = 10 * num + keypad_keyint(typed[i]);
                    i++;
                }
                intv[i] = '\0';
                intv_val = num;
                // reset for new values to enter correctly
                memset(typed, ' ', 15);
                typed[16] = '\0';
                c = 0;
            }
            else if (key == 'D')
            {
                // clear the old value to display the new
                i = 0;
                memset(meas, ' ', 15);
                meas[16] = '\0';
                // for the display
                while(typed[i] != '\0')
                {
                    if (typed[i] != 'A')
                    {
                        if (typed[i] != 'B')
                        {
                            if (typed[i] != 'C')
                            {
                                if(typed[i] != 'D')
                                {
                                    if (typed[i] != 'E')
                                    {
                                        if (typed[i] != 'F')
                                        {
                                            meas[i] = typed[i];
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // for the calculation
                    num = 10 * num + keypad_keyint(typed[i]);
                    i++;
                }
                meas[i] = '\0';
                intv_val = num;
                // reset for new values to enter correctly
                memset(typed, ' ', 15);
                typed[16] = '\0';
                c = 0;
            }
            else if (key = 'E')
            {
                
            }
        }
        else
        {
            LCD_print(1, "Intervals:");
            LCD_printf(2, intv);
            LCD_print(3, "# Measurements:");
            LCD_printf(4, meas);
        }
    }
    
    Sleep();
}



/* NOTES:
 * TRISx is used to set a digital I/O pin to be either an input or output.
 * PORTx is used for reading the value on the port pins.
 * LATx is used for setting outputs.
 */