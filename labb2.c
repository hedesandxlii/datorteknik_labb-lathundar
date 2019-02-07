void button_read_reliability() {
  /* code */
  #include yoda.h
 
  uint8_t current_state;
  uint8_t previous_state = 0;

  button_init();
  led_init();

  while (1)
  {
  	current_state = button_read(1);
 	 
  	if(current_state > previous_state)
  	{

    	led_toogle(0);  
   	 
  	}
	previous_state = current_state;
  }
 
}

void main(){

  usart0_init(191);
 
}

void usart0_init(unsigned int ubbr){
   /*Set baud rate */
   UBRR0H = (unsigned char)(ubrr>>8);
   UBRR0L = (unsigned char)ubrr;
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
   while ( !(UCSR0A & (1<<RXC)) );
   /* Get and return received data from buffer */
   return UDR0;
}

void usart0_transmit( unsigned char data )
{
   /* Wait for empty transmit buffer */
   while ( !( UCSR0A & (1<<UDRE)) );
   /* Put data into buffer, sends the data */
   UDR0 = data;
}

void timer3_init() {
  TCCR3A = (1<<WGM30)|(0<<WGM31)|(1<<WGM32)|(0<<WGM33);
  /*Behövs den här?*/
  TCCR3B |= 0b0001000;
  /*Borde funka men kanske behöver ovan rad (den kanske är smart tar det från TCCR3A) se sida 191 i manualen*/
  TCCR3B |= 0b0000101;

  /*Toggles pin b6 to be an output*/
  PORTB |= (1<<PB6);
  DDRB |= (1<<PB6);

  TCCR3A |= 0b010000;
 
}


void adc_init(){
  /*Enable ADC*/
  ADCSRA |= (1<<ADEN);

  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

  /*Sätter den till 0 för att vi inte behöver ändra något?*/
  ADMUX |= 0x00;

  /*Sätter reference voltage till AVcc*/
  ADMUX |= (0<<REFS1)|(1<<REFS0);
}
 



/*Start conversion*/
ADCSRA |= (1<<ADSC);

/*Read conversion*/
uint16_t adc_read(){
  return 0x0000 | ADCL | (ADCH<<8);
}

/*Home assignment 5.1  1/340m/s 2.94 ms */


/*Home assignment 5.2 varför 010*/
TCCR1B |= (0<<CS12)|(1<<CS11)|(0<<CS10)

/*Home assignment 5.3 2.27m*/

