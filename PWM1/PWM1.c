
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB |= (1<<PB4);
	PORTB |= (1<<PB4);
	
	TCCR0 |=(1<<WGM01); // enable fast PWM 
	TCCR0 |=(1<<WGM00); // enable fast PWM //pin3 (Fast PWM)
	TCCR0 |=(1<<COM01); // Clear OC0 on compare match, set OC0 at BOTTOM.
	TCCR0 |=(1<<CS01);  // set PRE-scaling with /8
	TCNT0
	
    while(1)
    {
        for(int i =0;i<=5;i++){
			OCR0=i*51; //Change D10 intensity according to OCR value
			_delay_ms(500);
		}
	
    }
}
/**************************************************
PWM : to enable TCCR0 WGM01 and WGM00 

**************************************************/