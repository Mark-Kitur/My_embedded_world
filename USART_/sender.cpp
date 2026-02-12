#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL


void USART_init(unsigned int ubrr) {
    // Baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable Tx and Rx, and 9-bit mode (UCSZ02)
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<UCSZ02);

    // Async mode, 8-bit + 9th bit = 9-bit frame, 2 stop bits
    UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}

void USART_Transmit(unsigned int data) {
    // Wait for transmit buffer empty
    while (!(UCSR0A & (1 << UDRE0)));

    // Set 9th bit
    if (data & 0x0100)
        UCSR0B |= (1<<TXB80);
    else
        UCSR0B &= ~(1<<TXB80);

    // Send lower 8 bits
    UDR0 = (unsigned char)data;
}
void USART_send_char( char word){
    while (!(UCSR0A & (1<<UDRE0)));

    UDR0 =word;
    
    }

void USART_send_string( const char* str){
    while (*str){
        USART_send_char(*str);
        str ++;
    }
}


int main(void) {
    USART_init(52); // 9600 baud @ 16 MHz
    _delay_ms(500);

    while (1) {
        USART_Transmit(13); // send number 13
        _delay_ms(2000);
        USART_send_string("MARK");

    }
}
