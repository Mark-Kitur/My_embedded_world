#define F_CPU 8000000UL
#include <avr/io.h>
#include "LCD_16x2_H_file.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define DA DDRA
#define DB DDRB
#define PTRB PORTB
#define PTRA PORTA


// global variable
char real_password[] = {'0', '9', '8', '7'};
// Function declaration
void tilt();
void change_password(char pass);
void show_it(char password);
void blue();
void red();
void ADC_Init();
uint16_t read_adc(uint8_t channel);
uint8_t check_keypad(int input_value);
void confirm_password(char see[]);

// ADC Initialization
void ADC_Init() {
	DDRA = 0x00;       
	ADCSRA = 0x87;     
	ADMUX = 0x40;     
}

// Read ADC value
uint16_t read_adc(uint8_t channel) {
	ADMUX &= 0xF0;         
	ADMUX |= channel;      
	ADCSRA |= (1 << ADSC); 
	while (ADCSRA & (1 << ADSC)); 
	return ADCW;           
}

// Main Function
int main(void) {
	DDRC = 0xFF;       
	char analog[10];
	ADC_Init();
	LCD_Init();

	// Enable INT2 interrupt2
	GICR = 1 << INT2;
	MCUCSR &= ~(1 << ISC2);  
	sei();                   
	LCD_String_xy(1,0,"ENTER PASSWORD");
	LCD_String_xy(2,0,"Press # to Pin");
	LCD_Command (0x0C);
	while (1) {
		
		tilt();
   
	}
}

int x=0;
int chunga =0;
ISR(INT2_vect) {
	LCD_Init();
	uint8_t pins[] = {PB4, PB5, PB6, PB7}; 
	uint8_t store = 0;

	for (int i = 0; i < 4; i++) {
		if (PINB & (1 << pins[i])) {       
			store |= (1 << i);          
		}
	}
	
	int converted = check_keypad(store);
	if(converted =='#' || x>=5){ // reset the password and update
		change_password(converted);
		x+=5;
		if(x>=90){
			x=0;
		}
	}
	else{
		show_it(converted); //reading the password and operate the safe
	}
}
int np=0;
//change password function
void change_password(char input) {
	static char entered_pass[5] = {0};static char new_pass[5] = {0};     
	static int step = 0;static int index = 0;LCD_Command(0x80);               
	if (input == '@') {             
		if (step == 0) {             
			LCD_Clear();
			if (strncmp(real_password, entered_pass, 4) == 0) {
				LCD_String("Enter New Pass:");
				step = 1;              
				} else {
				LCD_String("Wrong Password!");
				_delay_ms(1000);
				LCD_Clear();
				LCD_String("Try Again:");
				step = 0;             
			}
			memset(entered_pass, 0, sizeof(entered_pass));  // Reset entered password
			index = 0;  
			} else if (step == 1) {        
			LCD_Clear();
			LCD_String("Confirm Pass:");
			strncpy(new_pass, entered_pass, 4);  // Store new password
			memset(entered_pass, 0, sizeof(entered_pass));  // Reset entered password
			step = 2;                  
			index = 0;  
			} else if (step == 2) {        // Step 2: Confirm new password
			if (strncmp(new_pass, entered_pass, 4) == 0) {
				strncpy(real_password, new_pass, 4);  // Update the real password
				LCD_Clear();
				LCD_String("Password Updated!");
				} else {
				LCD_Clear();
				LCD_String("Mismatch!");
				_delay_ms(1000);
				LCD_Clear();
				LCD_String("Enter New Pass:");
				step = 1;  // Retry Step 1
			}
			memset(entered_pass, 0, sizeof(entered_pass));  
			memset(new_pass, 0, sizeof(new_pass));          // Reset new password
			index = 0;  // Reset index
		}
		} else if (input >= '0' && input <= '9') {  
		if (index < 4) {  
			entered_pass[index++] = input;
			LCD_Char('*');  
		}
	}
}



int y=0;
int ww=4;

// read the password as input and operate the safe
void show_it(char password) {
	static char pin[4];         
	static int y = 0;           
	static int ww = 4;         
	LCD_Command(0x80);
	LCD_Command(0xC4);
	if (password == '@') {     
		int correct = 1; 
		for (int q = 0; q < 4; q++) {
			if (real_password[q] != pin[q]) {
				correct = 0;  
				break;
			}
		}
		if (correct && y == 4) { 
			cli(); 
			red(); 
			sei();
			} else { 
			cli();
			LCD_String_xy(1, 0, "!!Wrong!!");
			LCD_String_xy(2, 0, "!PIN!");
			blue(); 
			sei();
		}
		
		
		y = 0;
		ww = 4;
		memset(pin, 0, sizeof(pin));
		}else if(password =='X'){
			LCD_Clear();
			for (int me = 0; me < y; me++) {
				LCD_Char(pin[me]); 
				_delay_ms(500);
			}
		}
		else { 
		if (y < 4) {
			pin[y] = password;
			LCD_String_xy(2, ww, "*");
			y++;
			ww++;
			} else {
			LCD_Clear();
			LCD_String_xy(1, 0, "Max 4 digits!");
			_delay_ms(1000);
			LCD_Clear();
			y = 0;
			ww = 4;
		}
	}
}
// Keypad Mapping
unsigned char keypad[4][4] = {
	{'7','8','9','/'},
	{'4','5','6','X'},
	{'1','2','3','-'},
	{'#','0','@','+'}
};
// reading Keypad function, using the MM74C922 IC
uint8_t check_keypad(int input_value) {
	int row = input_value / 4;
	int col = input_value % 4;

	if ((input_value >= 0) && (input_value < 16)) {
		return keypad[row][col];
	}
	return 0;
}

// Red Led Function
void blue() {
	for (int o=0;o<3;o++){
		PORTC |= (1 << PC6)|(1<<PC4);
		_delay_ms(300);
		PORTC &= ~((1 << PC6)|(1<<PC4));
		_delay_ms(100);
		
	}
	
}

// Blue LED Function
void red() {
	PORTA=(1<<PA7); // activate pull resistor
	LCD_String_xy(1, 0, "Push Button");
	LCD_String_xy(2, 0, "To Open");
	_delay_ms(900);
	LCD_Clear();
	for (int y=0;y<5;y++){
		PORTC = (1 << PC7) ;
		_delay_ms(1000);
		PORTC &= ~(1 << PC7);
		_delay_ms(600);
		// read the push button pin
		if ((PINA&(1<<PA7))==0){
			LCD_String("Pull handle");
			_delay_ms(500);
		}
		if(y==4){
			LCD_String_xy(1,0,"Time Out Safe");
			LCD_String_xy(2,0,"Closed!");
			_delay_ms(500);
		}
	}
	
}

// tilt function for detecting theft
void tilt() {
	ADC_Init();              
	PORTA |= (1 << PA6);    

	while (1) { 
		
		if ((PINA & (1 << PA6)) == 0) {
			break;              
		}              
		int read = read_adc(0); 
		if (read > 500) {
			cli();               
			blue();              
			LCD_Clear();         
			LCD_String_xy(0, 1, "Theft! Theft!");  
			_delay_ms(500);      
			LCD_Clear();         
			sei();               
		}
	}
}

