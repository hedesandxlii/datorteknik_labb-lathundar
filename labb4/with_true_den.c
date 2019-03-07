/*
 * GccApplication1.c
 *
 * Created: 2019-03-07 13:40:47
 * Author : an7821he-s
 */ 

#include <avr/io.h>
#include "true_den.h"

#define S1 (PINC & (1<<PINC6))>>(PINC6)
#define S2 (PINC & (1<<PINC7))>>(PINC7)
#define KOLLA (S2 | (S1)<<1)

char buffer[5];
int i = 0;

void initiateIoPins()
{
	DDRC &= ~((1<<PINC6)|(1<<PINC7));
	DDRB |= 0xFF;
}

int8_t getLionDelta() {
	// input sequences for in/out.
	// 0b(S2)(S1) to match the format in the handledning.
	char to_den[5] = {0b00,0b10,0b11,0b01,0b00};
	char to_wild[5] = {0b00,0b01,0b11,0b10,0b00};
	char reset[5] = {0,0,0,0,0};
	
	buffer[0] = KOLLA;	
	if(i < 5) {
		if(KOLLA != buffer[i-1]) {
			buffer[i] = KOLLA;
			i++;
		}
	} else {
		i = 0;
		memcpy(buffer, reset, 5);
	}
	if(memcmp(to_den, buffer, sizeof(buffer)) == 0) {
		return -1;
	} else if(memcmp(to_wild, buffer, sizeof(buffer)) == 0) {
		return 1;
	} else {
		// Don't change the counter if the input doesn't match any of the sequences.
		return 0;
	}
}

void print_lions_in_some_way(uint8_t lions) {
	PORTB &= 0;
	PORTB |= lions;
}

void main() {
 	initiateIoPins();
 	uint8_t lionsInWildy = 0;
// 	print_lions_in_some_way(lionsInWildy);
	security_system_init();
	while(1) {
		
 		lionsInWildy += getLionDelta();
 		if(lionsInWildy == 255) {
 			lionsInWildy = 0;
 		}
// 		print_lions_in_some_way(lionsInWildy);
		send_lions(lionsInWildy);
		security_system_run();
	}
}
