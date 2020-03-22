#include "Segment.h"

void Segment_Init(void){
	/* Setup DigitPos */
	POS_PORT_DDR = 0xFF;
	POS_PORT	 = 0xff;
	/* Setup DigitData */
	DATA_PORT_DDR = 0xff;
	DATA_PORT	  = 0x00;
	/* Enable Segments */
	SET_SEG1_DDR;
	ENABLE_SEG1;
	//SET_SEG2_DDR;
	//ENABLE_SEG2;
}
void Segment_DisplayDigit(unsigned char digitPos,unsigned char digitValue){
	unsigned char numbers[]= {ZERO, ONE, TWO, THREE, FOUR, FIVE\
	,SIX, SEVEN, EIGHT, NINE,DOT};
	
	POS_PORT = ~(1<<(digitPos-1));
	
	if(digitValue == '.')
	DATA_PORT = numbers[10];
	else
	DATA_PORT = numbers[digitValue];
	
	_delay_ms(10);
	
	POS_PORT = 0xff;
}