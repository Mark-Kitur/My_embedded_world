#include <avr/io.h>
#include <avr/interrupt.h>

void timer_delay();

int main(void) {
	DDRC = 0xFF;  /* Set PORTC as output */
	DDRD &= ~(1 << PD0); // Set PD0 as input for external clock

	/* Main loop */
	while (1) {
		PORTC = 0x01;  /* Pulse PC1 ON */
		timer_delay();  /* 20us delay */
		PORTC = 0x00;
		timer_delay();
	}
}

void timer_delay() {
	TCNT0 = 0;          // Initialize TCNT0 to 0
	TCCR0 = (1 << CS02) | (1 << CS00); // Set Timer0 to use external clock on T0 pin

	// Wait for the timer to overflow
	while ((TIFR & (1 << TOV0)) == 0); // Wait for TOV0 to roll over

	TCCR0 = 0;          // Stop the timer
	TIFR = (1 << TOV0); // Clear TOV0 flag
}