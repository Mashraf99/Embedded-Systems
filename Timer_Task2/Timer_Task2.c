#include <avr/io.h>
#define F_CPU 8000000
#include <avr/interrupt.h> //to use interrupts
#include <util/delay.h>

volatile int count=0; //volatile because this variable is transfered between multiple functions.

int main(void)
{
	sei();	//SREG |= (1<<8);
			//enable the global interrupt.
			
	DDRF |= (1<<PF1); // make PF1 as an output.
	PORTF |= (1<<PF1); //Enable the LEDs by make PF1 high.
		
	DDRA |= 0xFF; //make all LEDs as an output.
	PORTA |= 0x00; // close all LEDs.
		
	DDRB |= (1<<PB4);  //make LED D10 as an output.
	PORTB |= (1<<PB4); //make LED D10 on.
	
	TCCR0 |= (1<<CS01);  //Timer/Counter Control Register first 3 bits are re-scaler 010 -> /8
	TCCR0 |= (1<<WGM01); //Convert Timer to be in CTC mode
	TCCR0 |= (1<<COM00); //Toggle on compare match State.
	OCR0 = 99;			 //Output Compare Match.
	TIMSK |= (1<<OCIE0); //Timer/Counter Interrupt Mask Register Compare Match interrupt is enabled.
		
    while(1)
    {
		PORTA = 0xff;    //no | needed because that is overwrite.
						//Open all LEDs.
	}
}
ISR(TIMER0_COMP_vect){
	count++;
	if(count==5000){
		PORTA =0xAA;//no | needed because that is overwrite//10101010
		count=0;
		_delay_ms(200);
		
	}
}
/************************************************************************/
/* Timer Operation Modes:
-CTC:   Clear Timer On Compare Match.
		top value is OCR0 according to my set.

-Fast PWM
-PWM
-Normal                                                                   */
/************************************************************************/