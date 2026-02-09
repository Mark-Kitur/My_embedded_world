#include <avr/io.h>
#include <util/delay.h>

void USART_init(unsigned int ubrr){
    // Set baud
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr);

    // Enable receiver and transmitter, enable 9-bit mode (UCSZ02)
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<UCSZ02);

    // 9-bit, 2 stop bits
    UCSR0C = (1<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);
}

unsigned int USART_Receive(void){
    unsigned char status, data_low, ninth;

  
    while (!(UCSR0A & (1<<RXC0)));

    status = UCSR0A;
    ninth  = (UCSR0B & (1<<RXB80)) ? 1 : 0;
    data_low = UDR0;

    if (status & ((1<<FE0) | (1<<DOR0) | (1<<UPE0)))
        return 0xFFFF;    

    return (ninth << 8) | data_low;
}

int main(void){
    USART_init(52);   
    DDRC =0xff;

    while(1){
        unsigned int d = USART_Receive();
        if (d ==13){
            PORTC =(1<<PC0)|(1<<PC1)|(1<<PC2);
        }
    }
}
