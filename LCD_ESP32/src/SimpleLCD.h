/*
  SimpleLCD.h - Library for interfacing 20x4 LCD character display.
  Created by Raivis Strogonovs, August 6, 2013.
  Released into the public domain.
*/
#ifndef SimpleLCD_h
#define SimpleLCD_h

#include "Arduino.h"



class SimpleLCD
{
  public:
    SimpleLCD(int RS, int RW, int E, int D4, int D5, int D6, int D7);
    void lcdGoToXY(char x, char y);
    void lcdGoToAddr(char addr);
    void lcdInit();
    void lcdClear();
    void lcdWriteText(char *text);
    void lcdBusy();
    void sendCommand(char opCode);
    void sendCommand4Bit(char opCode);

  private:
	int _RS;
	int _RW;
	int _E;
	int _D4;
	int _D5;
	int _D6;
	int _D7;
};

#endif
