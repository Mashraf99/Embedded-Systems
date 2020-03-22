#include <avr/io.h>
#include <avr/interrupt.h>
#include "Segment.h"

volatile int count=0; //volatile because this variable is transfered between multiple functions.

int main(void)
{
	sei();	//SREG |= (1<<8);
	//enable the global interrupt.
	
	//ADMUX |= (1<<REFS0); // Internal 2.56V Voltage Reference with external capacitor at AREF pin 
	ADMUX |= (1<<REFS1); // AVCC with external capacitor at AREF pin
	ADMUX |= (1<<ADLAR); // 1 :- MSB at ADCH
						 // default selecting AD0
						 
	ADCSRA |= (1<<ADEN); // Enable ADC
	ADCSRA |= (1<<ADSC); // Start convention (Just one time and then it goes low)
	ADCSRA |= (1<<ADFR); // continue conventionalizing (set ADSC to be high again )
	
		
	DDRB |= (1<<PB4);  //make LED D10 as an output.
	PORTB |= (1<<PB4); //make LED D10 on.

	TCCR0 |= (1<<CS01);  //Timer/Counter Control Register first 3 bits are re-scaler 010 -> /8
	TCCR0 |= (1<<WGM01); //PWM
	TCCR0 |=(1<<WGM00); // enable fast PWM //pin3 (Fast PWM)
	TCCR0 |= (1<<COM01); //clear on compare match State.
	
	PORTE |= (1<<PE4);
	
	OCR0 = ADCH;			 //Output Compare Match.PB4
	 Segment_Init();

	while(1)
	{
		
	OCR0 = ADCH;
	Segment_DisplayDigit(3,OCR0%10);
	Segment_DisplayDigit(2,(OCR0/10)%10);
	Segment_DisplayDigit(1,OCR0/100);
	
	}
}