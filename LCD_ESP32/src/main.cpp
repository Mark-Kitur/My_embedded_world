#include <Arduino.h>
#include "SimpleLCD.h"

const int RS= 0;
const int RW= 4;
const int E = 2;
const int D4= 12;
const int D5= 13;
const int D6 =15 ;
const int D7= 32;

SimpleLCD lcd(RS,RW,E,D4,D5,D6,D7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.lcdInit();
  // lcd.lcdWriteText("--> Hello Kitur<--");
  // lcd.lcdGoToXY(1,3);
  // lcd.lcdWriteText("weka mawe");
  // lcd.lcdGoToXY(2,4);
  // lcd.lcdWriteText("engineer");
  char name [] ="MARK";

  lcd.lcdGoToXY(3,0);
  lcd.lcdWriteText(name);
}

void loop() {
  // put your main code here, to run repeatedly:
}
