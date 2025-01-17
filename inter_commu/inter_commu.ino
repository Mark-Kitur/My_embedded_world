#include <Wire.h>
#define slave1 13
int led =13;
int read;
int main(){
  pinMode(led,OUTPUT);
  Wire.begin(slave1);
  Wire.onReceive(receive);
}
void loop(){
  read= Wire.read();
  
}
void receive(){
  if (read==1){
    for(int r=0;r<20;r++){
      digitalWrite(led,1);
      delay(50);
      digitalWrite(led,0);
      delay(50);
    }
  }
}