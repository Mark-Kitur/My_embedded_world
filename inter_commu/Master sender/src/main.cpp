#include <Arduino.h>
#include <Wire.h>
#define  slave1 13
int  button=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT_PULLUP);
  // enable pin interrupt 2
  PCICR |= (1 << PCIE2); 
  // Enable interrupt for pin 2 (PCINT18)
  PCMSK2 |= (1 << PCINT18); 

  // communications
  Wire.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}
ISR(PCINT2_vect){
  Serial.println("Starting to transmit.....");
  Wire.beginTransmission(slave1);
  Wire.write(1);
  Wire.endTransmission();
  Serial.println("End of transmisssion");
}
