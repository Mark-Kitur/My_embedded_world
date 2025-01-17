#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
void PWM_Init(){
	/*set fast PWM mode with non-inverted output*/
	// The PWM uses timer 0;
	TCCR0 =0x6B;
	DDRB|=(1<<PD3);  /*set OC0 pin as output*/
}

void ADC_Init(){
	DDRA =0x00;
	ADCSRA =0x87; // enable adc fr/128
	ADMUX= 0x40; // Avcc, channel 0
}
int ADC_Read(char channel){
	int Ain,AinLow;
	ADMUX =ADMUX|(channel&0x0f); // set input channel
	
	ADCSRA |= (1<<ADSC); //start convertion
	while((ADCSRA&(1<<ADIF))==0);
	_delay_ms(10);
	AinLow =(int)ADCL;
	Ain =(int)ADCH*256;
	
	Ain = Ain+AinLow;
	
	return(Ain);
}
int map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main(void){
	PWM_Init();
	ADC_Init();
	
	
	while(1){
		int cycle_value = ADC_Read(0);
		int mapped =map(cycle_value,0,1023,0,255);
		OCR0 = mapped;
		
	}
}