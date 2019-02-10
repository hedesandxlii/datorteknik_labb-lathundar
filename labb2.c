/*
 * GccApplication1.c
 *
 * Created: 2019-02-07 15:57:41
 * Author : an7821he-s
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "yoda.h"
#include <util/delay.h>

void statefull_button_pleb();
void statefull_button_pro();
void statefull_button_proest ();
int button_read_reliability();
void usart0_init(unsigned int ubbr);
unsigned char usart0_receive(void);
void usart0_transmit(unsigned char data);
void timer3_init();
void set_period(uint16_t);
void set_pulse(uint16_t);
void pwm_stoff(uint16_t);
void timer1_init();
void uss_run();
void set_pwm(uint16_t, uint16_t);

int main(void)
{
	/* Replace with your application code */
	
	//pwm_stoff(0x00ff);
	timer3_init();
	timer1_init();
	while (1)
	{
		uss_run();
		set_pwm(TCNT1*255/(2^16-1), 0x00ff);
	}
	
}

void statefull_button_pleb () 
{
	int *ledInit = 0x24; // set pointer to address of DDRB
	int *ledData = 0x25; // set pointer to address of PORTB
	int *buttonInit = 0x21; // set pointer to address of DDRA
	volatile int *buttonData = 0x20; // set pointer to address of PINA

	*ledInit |= 0b00000001; // set data direction to output for led3
	*buttonInit |= 0b00000000; // set data direction to input
	
	while(1) {	
		if((*buttonData & 0b00100000) >> 5) {
			if(*ledData == 1) {
				*ledData = 0;
				} else {
				*ledData = 1;
			}
			// Noise kanske sabbar detta. Noise sabbade det inte :)
			while((*buttonData & 0b00100000) >> 5){}
		}
	}
}

void statefull_button_pro ()
{
	DDRB |= 0b00000001; // set data direction to output for led3
	DDRD |= 0b00000000; // set data direction to input for buttons
	
	while(1) {
		if(PIND >> PORTD7) {
			if(PORTB) {
				PORTB = 0;
				} else {
				PORTB = 1;
			}
			while(PIND >> PORTD7){}
		}
	}
}

void statefull_button_proest () 
{
	DDRB |= 0b00000001; // set data direction to output for led3
	DDRD |= 0b00000000; // set data direction to input for buttons
	
	while(1) {
		if(button_read_reliability()) {
			if(PORTB) {
				PORTB = 0;
				} else {
				PORTB = 1;
			}
			while(button_read_reliability()){}
		}
	}
}

int button_read_reliability()
{
	/*
		Idé: Hoppa över alla gropar och kolla värdet på första flanken och efter 50ms.
		Vi har provat oss fram till 50ms.
	*/
	while (1)
	{
		if(PIND >> PORTD7)
		{
			_delay_ms(50);
			return PIND >> PORTD7;
		}
	}
}

void usart_stoff()
{
	usart0_init(103);
	while(1){
		usart0_transmit(usart0_receive());
	}
}

void usart0_init(unsigned int ubbr)
{
   /*Set baud rate */
   UBRR0 = ubbr;
   /*Enable receiver and transmitter */
   UCSR0B = (1<<RXEN0)|(1<<TXEN0);
   /* (0<<USBS0) skiftar USBS0 biten dvs stop biten till 0 dvs 1-bit stop
  	(3<<UCSZ00) skiftar UCSZ00 biten till 3 (011) och då får vi 8-bitar data lenght
   */
   UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

unsigned char usart0_receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<7)) ); // RXC = 7
	/* Get and return received data from buffer */
	return UDR0;
}

void usart0_transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<5)) ); //UDRE = 5
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void timer3_init()
{
	// Clear on comparison match.
	TCCR3A |= (1<<COM3A1);
	//TCCR3A |= (1<<COM3B1) | (0<<COM3B0);
	
	// Fast PWM config
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM32)|(1<<WGM33);
	/*Gammal kommentar: "Borde funka men kanske behöver ovan rad (den kanske är smart tar det från TCCR3A) se sida 191 i manualen"*/
	TCCR3B |= (1<<CS30)|(1<<CS32);
	//TCCR3B &= ~(1<<CS31);

	/*Toggles pin b6 to be an output*/
	DDRB |= (1<<PORTB6)|(1<<PORTB7);
	//PORTB |= OCR3A;
	//DDRB |= (1<<OCR0A);

	//TCCR3A |= 0b010000;
	
}

void set_pulse(uint16_t arg)
{
	// Enl. s.156 måste den låga byten accessas först, men i C sköter compilern det.
	OCR3A = arg;
	//OCR3AL = arg;
	//OCR3AH = arg >> 8;
}

void set_period(uint16_t ocr)
{
	// Enl. s.156 måste den låga byten accessas först, men i C sköter compilern det.
	ICR3 = ocr;
	//ICR3L = ocr;
	//ICR3H = ocr >> 8;
}

void pwm_stoff(uint16_t period)
{
	timer3_init();
	set_pulse(0);
	set_period(period);
	uint16_t puls = 0;
	uint16_t delta = 1;
	
	while(1){
		if(puls >= ICR3) {
			delta = -1;
		}
		if(puls == 0) {
			delta = 1;
		}
		puls += delta;
		set_pulse(puls);
		_delay_ms(10);
	}
}

void set_pwm(uint16_t pulse, uint16_t period)
{
	set_pulse(pulse);
	set_period(period);
}

void timer1_init()
{
	TCCR1B &= ~((1<<CS10)|(1<<CS11)|(1<<CS12));
	/**/
	DDRC |= (1<<PORTC1)|(0<<PINC0);
}

void uss_run()
{
	// Clears timer before measurement
	TCNT1 = 0;
	// Creates a trigger pulse.
	PORTC |= (1<<PORTC1);
	_delay_us(10);
	PORTC &= ~(1<<PORTC1);

	// Waits for echo to go high
	while(!PINC) {}
	TCCR1B |= (1<<CS10);// Starts counter after echo goes high by setting prescaler value to 1.
	
	// Waits for echo to go low.
	while(PINC) {}
	// Stops counter after echo goes low by removing prescaler value.
	TCCR1B &= ~((1<<CS10)|(1<<CS11)|(1<<CS12)); 
	
	_delay_ms(60);
}
