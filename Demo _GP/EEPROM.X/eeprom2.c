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
  
    for(i = 8;i>=0;i-- ){
    LATCbits.LATC4 = 0;
    LATCbits.LATC4 = 1;
    }
}

void writeAddr(int output){
    
    int i;
    int mask;
    mask = 0x80;
    for(i = 7;i>=0;i-- ){
    LATCbits.LATC6 = (mask & output)>> i;
    mask = mask/2; 
    LATCbits.LATC7 = 0;
    LATCbits.LATC7 = 1;
    }
}

void writeData(int output){
    
    int i;
    int mask;
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
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISCbits.RC5 = 0; 
    TRISCbits.RC4 = 0; 
    TRISCbits.RC3 = 0;
    TRISCbits.RC1 = 0;
    TRISCbits.RC0 = 1;

    
    
   
writeData(0x00);
writeAddr(0xAA);
recieved = readDATA();
Delay10KTCYx(10);
writeData(0xAA);
writeAddr(0xFF);
recieved = readDATA();
Delay10KTCYx(10);
writeData(0xFF);
writeAddr(0x80);
recieved = readDATA();
 Delay10KTCYx(10);
 clrData();
 Delay10KTCYx(10);
 recieved = readDATA();
 Delay10KTCYx(10);
 writeData(0x80);
 writeAddr(0x00);
 recieved = readDATA();
Delay10KTCYx(10);
 Nop();
}


