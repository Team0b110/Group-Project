#include <p18f452.h>
#include <delays.h>
#include <p18cxxx.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF

void clrData(){
    
      int i;
    LATCbits.LATC4 = 0;
    LATCbits.LATC5 = 0;
    LATEbits.LATE2 = 0;
    for(i = 8;i>=0;i-- ){
    LATCbits.LATC4 = 0;
    LATCbits.LATC4 = 1;
    }
}

void writeAddr(int output){
    
    int i;
    int mask;
    mask = 0x8000;
    for(i = 15;i>=0;i-- ){
    LATCbits.LATC6 = (mask & output)>> i;
    mask = mask/2; 
    LATCbits.LATC7 = 0;
    LATCbits.LATC7 = 1;
    }
}

void writeData(int output){
    
    int i;
    int mask;
    LATEbits.LATE2 = 1;
    mask = 0x80;
    for(i = 7;i>=0;i-- ){
    LATCbits.LATC5 = (mask & output)>> i;
    mask = mask/2; 
    LATCbits.LATC4 = 0;
    LATCbits.LATC4 = 1;
    }
}

int readDATA(){
    int i;
    int input;
    input = 0;
    LATCbits.LATC3= 0; 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC3= 1; 
    LATEbits.LATE2 = 0;
    
   
    for(i = 0;i<8;i++ ){
    input = input<< 1;
    input = input | PORTCbits.RC0; //adding bit to the end 
    LATCbits.LATC1 = 0;
    LATCbits.LATC1 = 1;
    }
    return input;
}
     
    

void main(void){
    int recieved; 
    recieved=0;
    LATCbits.LATC7 = 0;
    LATCbits.LATC6 = 0;
    LATCbits.LATC5 = 0;
    LATCbits.LATC4 = 0;
    LATDbits.LATD3 = 1;
    LATAbits.LATA6 = 1;
    LATEbits.LATE2 = 0;
    
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC5 = 0; 
    TRISCbits.RC4 = 0; 
    TRISCbits.RC3 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC0 = 1;
    TRISDbits.RD3 = 0; //OE
    TRISAbits.RA6 = 0 ;//WE 
    TRISEbits.RE2 = 0 ;

LATDbits.LATD3 = 1;
LATAbits.LATA6 = 1;
writeAddr(0x5555);
writeData(0xAA);
LATAbits.LATA6 = 0;
LATAbits.LATA6  = 1;
writeAddr(0x2AAA);
writeData(0x55);
LATAbits.LATA6 = 0;
LATAbits.LATA6 = 1;
writeAddr(0x5555);
writeData(0xA0);
LATAbits.LATA6 = 0;
LATAbits.LATA6 = 1;
Nop(); 
writeAddr(0x0003);
writeData(0xAA);
LATAbits.LATA6 = 0;
LATAbits.LATA6 = 1;
Delay10TCYx(1);
Nop();
Nop();
LATDbits.LATD3 = 0;
recieved = readDATA();
Nop(); 
Nop(); 

}



