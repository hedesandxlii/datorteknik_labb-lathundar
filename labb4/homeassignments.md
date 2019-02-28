# Home assignments
## Anteckningar
```
Sensor S1 = PINC7
Sensor S2 = PINC6
```

Vi får inte använda en `while`-loop som break:ar när ett lejon gått genom grinden.


## HA1.1
```
void initiateIoPins() 
{
    DDRC &= ~((1<<PINC6)(1<<PINC7))
}
```

## HA1.2
```
#define S1 = PINC6
#define S2 = PINC7

void main() {
    uint8_t lionsInWildy = 0;
    while(1) {
        lionsInWildy += getLionDelta();
        print_lions_in_some_way(lionsInWildy);
    }
}
int8_t getLionDelta() {
    // idle
    while(!(S1 || S2)) {
        // Lion to wildy
        while(S2 && !S1) {
            // Lion in the middle
            while(S2 && S1) {
                // Cat free
                while(!S2 && S1) {
                    if(!(S2 || S1)) {
                        return 1;
                    }
                }
            }
        }
        // Lion going to da den
        while(!S2 && S1) {
            // Lion in the middle
            while(S2 && S1) {
                // Lion almost there
                while(S2 && !S1) {
                    // Cat caged
                    if(!(S2 || S1)) {
                        return -1;
                    }
                }
            }
        }
    }
}
```

## HA2.1 -> HA2.3
```
//PC7 <--> PCINT23
//PC6 <--> PCINT22
// Enable interupt from our pins.
PCMSK2 |= (1<<PCINT23)(1<<PCINT22);
// Enable above interrupts fo' real
PCICR |= (1<<PCIE2);
// Enable global interrupt
SREG |= (1<<I) // I = 7. "sei()" kan också användas.
```

## HA2.4
```
// Någon av dessa ska användas.
USDR0B |= 1<<RXCIE
USDR1B |= 1<<RXCIE
```
