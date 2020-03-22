#include <avr/io.h>

int main(void)
{
	ADMUX |= (1<<REFS0); // AREF, Internal V ref turned off
	ADMUX |= (1<<REFS1); // AREF, Internal V ref turned off
	ADMUX |= (1<<ADLAR); // 1 :- MSB at ADCH

	// default selecting AD0

	//REC 1 is front right
	ADMUX |= 0x07; //REC 1

	ADCSRA |= (1<<ADEN); // Enable ADC
	ADCSRA |= (1<<ADSC); // Start convention (Just one time and then it goes low)
	ADCSRA |= (1<<ADFR); // continue conventionalizing (set ADSC to be high again )



	DDRF |= (1<<PF1); // direction
	PORTF |= (1<<PF1); //enable

	DDRA |= 0xFF;


    while(1)
    {
		PORTA = ADCH ;


    }
}
/***********************
signaL MUST BE IN THe range of 5 to 0 volt.
ADC:
8 bit or less or more
more bits is better (not optional)
less scope is better
fast clock is better
better for low quantization

AREF : hardware pin to select the max scale of voltage
ADLAR : 0 :- MSB at ADCL
		1 :- MSB at ADCH

we can make interrupt on ADC by using this register ADCSRA -> ADIF
we can enable interrupt on ADC by using this register ADCSRA -> ADIE


*************************/



uint16_t Front_Right(void) {
	ADMUX |= (1 << REFS0); // AVCC with external capacitor at AREF pin
	//ADMUX |= (1 << ADLAR); // 1 :- MSB at ADCH
	ADMUX |= 0x07; //REC 1 //REC 1 is front right
	
	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)

	int read1,read2;
	
	read1= ADC; //when transmitters are off

	DDRD |= (1 << PD7); // direction
	PORTD |= (1 << PD7); //enable the Transmitters

	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)

	read2 = ADC; //when transmitters are on

	PORTD &= ~(1 << PD7); //disable the Transmitters

	return (read2-read1); //subtract the noise
}

uint16_t Front_Left(void) {
	ADMUX |= (1 << REFS0); // AVCC with external capacitor at AREF pin
	//ADMUX |= (1 << ADLAR); // 1 :- MSB at ADCH
	ADMUX |= 0x03; //REC 4 //REC 4 is front left
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // pr-scaler = 128
	ADCSRA |= (1 << ADEN); // Enable ADC
	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)

	int read1,read2;
	
	read1 = ADC; //when transmitters are off

	DDRD |= (1 << PD7); // direction
	PORTD |= (1 << PD7); //enable the Transmitters

	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)

	read2 = ADC; //when transmitters are on

	PORTD &= ~(1 << PD7); //disable the Transmitters

	return (read2 - read1); //subtract the noise
}

uint16_t Right(void) {
	ADMUX |= (1 << REFS0); // AVCC with external capacitor at AREF pin
	//ADMUX |= (1 << ADLAR); // 1 :- MSB at ADCH
	ADMUX |= 0x06; //REC 2 // right
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // pr-scaler = 128
	ADCSRA |= (1 << ADEN); // Enable ADC
	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)
	
	while(ADCSRA & (1<<ADSC));
	int read1,read2;
	read1 = ADC ;//when transmitters are off

	DDRD |= (1 << PD7); // direction
	PORTD |= (1 << PD7); //enable the Transmitters

	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)
	while(ADCSRA & (1<<ADSC));
	read2 = ADC ;//when transmitters are on

	PORTD &= ~(1 << PD7) ;//disable the Transmitters
	
	return (read2 - read1); //subtract the noise
}
uint16_t Left(void) {
	ADMUX |= (1 << REFS0); // AVCC with external capacitor at AREF pin
	//ADMUX |= (1 << ADLAR); // 1 :- MSB at ADCH
	ADMUX |= 0x04; //REC 5 left
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // pr-scaler = 128
	ADCSRA |= (1 << ADEN); // Enable ADC
	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)
	
	int read1,read2;
	read1 = ADC; //when transmitters are off

	DDRD |= (1 << PD7); // direction
	PORTD |= (1 << PD7); //enable the Transmitters

	ADCSRA |= (1 << ADSC); // Start convention (Just one time and then it goes low)

	read2 = ADC ;//when transmitters are on

	PORTD &= ~(1 << PD7) ;//disable the Transmitters

	return (read2 - read1); //subtract the noise
}

