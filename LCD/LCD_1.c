/*
 * LCD_1.c
 *
 * Created: 09/07/2019 12:05:38 ص
 *  Author: cisco126
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util//delay.h>
#include "lcd.h"
int main(void)
{
	PORTE |= (1<<PE4);
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
			
	OCR0 = ADCH;			 //Output Compare Match.PB4
			
	LCD_Init();
	 char a;
	 char b;
	 char c;
	
    while(1)
    {
			OCR0 = ADCH;
			a=(ADCH/100)+0x30;
			b=((ADCH/10)%10)+0x30;
			c=(ADCH%10)+0x30;
			LCD_DispCharXY(1,1,a);
			LCD_DispCharXY(2,1,b);
			LCD_DispCharXY(3,1,c);
			
		
	}
}