#ifndef SEGMENT_H_
#define SEGMENT_H_

#ifndef F_CPU
	#define F_CPU	8000000UL
#endif

#include "avr\io.h"
#include "util\delay.h"
//#include "data_types.h"

#define ZERO   0x3f	//0xC0//
#define ONE	   0x06	//0xF9
#define TWO	   0x5b	//0xA4
#define THREE   0x4f	//0xB0
#define FOUR	0x66//0x99
#define FIVE	0x6d//0x92
#define SIX		0x7d//0x82
#define SEVEN	0x07//0xF8
#define EIGHT	0x7f//0x80
#define NINE	0x6f//0x90
#define DOT		0x80//0x7F

#define POS_PORT				PORTA
#define POS_PORT_DDR			DDRA

#define DATA_PORT				PORTC
#define DATA_PORT_DDR			DDRC

#define ENABLE_SEG1				PORTF &= ~(1<<PF2);
#define SET_SEG1_DDR			DDRF |= (1<<PF2)

//#define ENABLE_SEG2				PORTF |= (1<<PF2)
//#define SET_SEG2_DDR			DDRF |= (1<<PF2)


void Segment_Init(void);
void Segment_DisplayDigit(unsigned char digitPos,unsigned char digitValue);

#endif /* SEGMENT_H_ */