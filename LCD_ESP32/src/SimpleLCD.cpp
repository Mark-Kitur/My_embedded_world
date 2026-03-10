/*
  SimpleLCD.h - Library for interfacing 20x4 LCD character display.
  Created by Raivis Strogonovs, August 6, 2013.
  Released into the public domain.
*/

#include "Arduino.h"
#include "SimpleLCD.h"

SimpleLCD::SimpleLCD(int RS, int RW, int E, int D4, int D5, int D6, int D7)
{
	_RS = RS; _RW = RW; _E = E;
	_D4 = D4; _D5 = D5; _D6 = D6; _D7 = D7;

	pinMode(_RS, OUTPUT);   
	pinMode(_RW, OUTPUT); 
	pinMode(_E, OUTPUT); 
	pinMode(_D4, OUTPUT); 
	pinMode(_D5, OUTPUT); 
	pinMode(_D6, OUTPUT); 
	pinMode(_D7, OUTPUT);
}

void SimpleLCD::lcdGoToXY(char x, char y)
{
  char addr;
  switch(x)
  {
     case 0: addr = 0x00; break; //Starting address of 1st line
     case 1: addr = 0x40; break; //Starting address of 2nd line
     case 2: addr = 0x14; break; //Starting address of 3rd line
     case 3: addr = 0x54; break; //Starting address of 4th line
     default: ; 
  }
  
  addr +=y;
  
  lcdGoToAddr(addr);
}

void SimpleLCD::lcdGoToAddr(char addr)
{
    char cmd = 0x80 | addr;
    digitalWrite(_RS, LOW);
    digitalWrite(_RW, LOW);
    sendCommand4Bit(cmd);
}

void SimpleLCD::lcdInit()
{
  //Set all the control pins to logic Zero
  digitalWrite(_RS, 0);
  digitalWrite(_RW, 0);
  digitalWrite(_E, 0);
  
  
  //Do the wake up call
  delay(20);
  sendCommand(0x30);
  delay(20);
  sendCommand(0x30);
  delay(20);
  sendCommand(0x30);  
  delay(20);
  sendCommand(0x20);  //Let's make it 4 bit mode
  delay(10);
  //That's it LCD is initialized in 4 bit mode.
  
  
  sendCommand4Bit(0x28); //N = 1 (2 line display) F = 0 (5x8 characters)
  sendCommand4Bit(0x08); //Display on/off control D=0,C=0, B=0 
  sendCommand4Bit(0x01); //Clear Display
  sendCommand4Bit(0x06); //Entry mode set - I/D = 1 (increment cursor) & S = 0 (no shift) 
  sendCommand4Bit(0x0C); //Display on/off control. D = 1, C and B = 0. (Cursor and blink, last two bits)  
}

void SimpleLCD::lcdClear()
{
   digitalWrite(_RS, LOW);
   digitalWrite(_RW, LOW);
   sendCommand4Bit(0x01);
}

 void SimpleLCD::lcdWriteText(char *text)
 {
       
 	while( *text)
 	{
                digitalWrite(_RS,HIGH);
 		sendCommand4Bit(*text++);
 	}
 }

void SimpleLCD::lcdBusy()
{
  digitalWrite(_RS, LOW);
  pinMode(_D7, INPUT);
  digitalWrite(_RW, HIGH);  
  
  int busyFlag = 1;
  while(busyFlag == 1)
  {
    //The data should be read while Enable pin is HIGH
    digitalWrite(_E, HIGH); 
           busyFlag = digitalRead(_D7);
    digitalWrite(_E, LOW);                 
    
    //Clock out the lower part of data, since we are interested in only the 
    //upper part. more precissaley D7 pin.
    digitalWrite(_E, HIGH);                 
    digitalWrite(_E, LOW);                 
  }
  pinMode(_D7, OUTPUT);
  digitalWrite(_RW, LOW);
}

void SimpleLCD::sendCommand(char opCode)
{  
  digitalWrite(_D4, opCode & 0x10);
  digitalWrite(_D5, opCode & 0x20);
  digitalWrite(_D6, opCode & 0x40);
  digitalWrite(_D7, opCode & 0x80);
}

void SimpleLCD::sendCommand4Bit(char opCode)
{
  digitalWrite(_D4, opCode & 0x10);
  digitalWrite(_D5, opCode & 0x20);
  digitalWrite(_D6, opCode & 0x40);
  digitalWrite(_D7, opCode & 0x80);
  digitalWrite(_E,HIGH);
  digitalWrite(_E,LOW);
  digitalWrite(_D4, opCode & 0x01);
  digitalWrite(_D5, opCode & 0x02);
  digitalWrite(_D6, opCode & 0x04);
  digitalWrite(_D7, opCode & 0x08);
  digitalWrite(_E,HIGH);
  digitalWrite(_E,LOW);
  lcdBusy();
}
