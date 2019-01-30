// Uppg 2.1
led_init()
button_init()

while(true){
  if(button_read(1)) {
    led_on(1);
  } else {
    led_off(1);
  }
}

// Uppg 6.1
#include "util/delay.h"

led_init()
while(true) {
  led_on(1);
  _delay_ms(500);
  led_off(1);
  _delay_ms(500);
}

// Uppg 6.2, c-fil till elf.
avr-gcc -mmcu Atmega1284 <cfilen> -o output.elf -I . -L . -lyoda

// Uppg 6.3, elf till ihex
avr-objcopy -j .text .data -O ihex <elf> <output(hex)>

// Uppg 6.4, instruktioner fr elf
avr-objdump -d <elf>
