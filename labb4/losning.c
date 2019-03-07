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
	// input sequences for in/out.
	char to_den[5] = {0b00,0b10,0b11,0b01,0b00};
	char to_wild[5] = {0b00,0b01,0b11,0b10,0b00};
	char buffer[5];
	buffer[0] = KOLLA;	
	for(int i = 1; i < 5;) {
		if(KOLLA != buffer[i-1]) {
			buffer[i] = KOLLA;
			i++;
		}
	}
	if(memcmp(to_den, buffer, sizeof(buffer)) == 0) {
		return -1;
	} else if(memcmp(to_wild, buffer, sizeof(buffer)) == 0) {
		return 1;
	} else {
		return 0;
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
