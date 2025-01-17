#include <avr/io.h>
#define  F_CPU 8000000UL 
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

#define A PORTA
#define B PORTB
#define C PORTC
#define D PORTD

#define da DDRA
#define db DDRB
#define dc DDRC
#define dd DDRD
// outputs
void first();
void second();
void third();
char nums [] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00};
void ADC_(void){
	da= 0x00;
	ADCSRA =0x87;
	ADMUX =0xC0;
}
int compute(int channel){
	int Ain, AinLow;
	ADMUX = ADMUX |(channel);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA &(1<<ADIF))==0);
	_delay_ms(10);
	
	AinLow =(int) ADCL;
	Ain = (int)ADCH*256;
	Ain += AinLow;
	return Ain;
}
int main(void)
{
	dd=0xFF;
	dc=0xFF;
	db=0xFF;
	ADC_();
    while (1) 
    {
		int val =compute(0);
		int hud = val/100;
		int dummy=val%100;
		int tens= dummy/10;
		int ones=dummy%10;
		
		first(ones);
		second(tens);
		third(hud);
	}
}

void first(int digit){
	B = nums[digit];
}

void second(int digit) {
	D =nums[digit];
}
void third (int digit){
	C = nums[digit];
}