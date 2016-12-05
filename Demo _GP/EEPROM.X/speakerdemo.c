#include <p18cxxx.h>
#include <delays.h>
#include <pwm.h>
#include <timers.h>
#include <delays.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#define XTAL_FREQ  4000000

//#define C 0x19 prescaler of 16
//#define D 0x16
//#define E 0x14
//#define F 0x12
//#define G 0x10
//#define A 0x0E
//#define B 0x0D
//#define C2 0x0C

#define C 0x65 //prescaler of 16



int i;

void main(void)

{
    TRISCbits.TRISC2 = 0;
    SetDCPWM1(30);
    OpenTimer2(TIMER_INT_OFF & T2_PS_1_4 & T2_POST_1_1);
    while(1)
    {
        //play x notes inside song array
      
   
        OpenPWM1(C);
                               //set PWM frequency according to entries in song array

        Delay10KTCYx(100);
      OpenPWM1(1); //the PWM frequency set beyond audible range
                                          //in order to create a short silence between notes
      Delay10KTCYx(25);   //the silence is played for 50 ms                  
      
    }
    Sleep(); 
}