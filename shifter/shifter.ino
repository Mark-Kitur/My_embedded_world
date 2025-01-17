int DS_pin =2;
int STCP_pin= 4;
int Shcp_pin = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin,OUTPUT);
  pinMode(STCP_pin,OUTPUT);
  pinMode(Shcp_pin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000000001);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000000011);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000000111);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000001111);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000011111);
  digitalWrite(STCP_pin, 1);
  delay(100);
  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0000111111);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0001111111);
  digitalWrite(STCP_pin, 1);
  delay(100);

  digitalWrite(STCP_pin,0);
  shiftOut(DS_pin,Shcp_pin,LSBFIRST,0B0011111111);
  digitalWrite(STCP_pin, 1);
  delay(100);
  

}
