/*
 * GccApplication1.c
 *
 * Created: 2019-03-07 13:40:47
 * Author : an7821he-s
 */ 

#include <avr/io.h>

#define S1 (PINC & (1<<PINC6))>>(PINC6)
#define S2 (PINC & (1<<PINC7))>>(PINC7)
#define KOLLA (S2 | (S1)<<1)

void initiateIoPins()
{
	DDRC &= ~((1<<PINC6)|(1<<PINC7));
	DDRB |= 0xFF;
}

int8_t getLionDelta() {
	char buffer[5];
	buffer[0] = KOLLA;	
	for(int i = 1; i < 5;) {
		if(KOLLA != buffer[i-1]) {
			buffer[i] = KOLLA;
			i++;
		}
	}
	if(buffer[1] == 0b0000010 && buffer[3] == 0b0000001) { // way in to den
		return -1;
	} else if(buffer[1] == 0b0000001 && buffer[3] == 0b0000010) { // way out to wildy
		return 1;
	}

 		
}

void print_lions_in_some_way(uint8_t lions) {
	PORTB &= 0;
	PORTB |= lions;
}

void main() {
	initiateIoPins();
	uint8_t lionsInWildy = 0x00;
	print_lions_in_some_way(lionsInWildy);
	while(1) {
		//PORTB &= 0x00;
 		//PORTB |= KOLLA;
		uint8_t lionDelta = getLionDelta();
		lionsInWildy += lionDelta;
		print_lions_in_some_way(lionsInWildy);
	}
}
