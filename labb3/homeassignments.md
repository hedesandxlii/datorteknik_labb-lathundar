# HOME ASSIGNMENTS LABB 3
## 1.1

```
t = 0.1s
f = 16 *10^6

t * f = 1.6 miljoner
```

## 1.2

```
21 bitar (2^31 = 2 097 152)
```

## 1.3

Vi behöver 3 8-bitars register.

## 1.4

```
#define R16 first
#define R17 second
#define R18 third

; De 2 första registerna används som prescalers.
; Vi kommer ha en minsta skillnad på ~4ms
; 0.1 s <=> 1.6 * 10^6 cykler
; Typiska round i loopen är 6 cykler(bara first som incrementeras)
; Antal rundor = 1.6 * 10^6 cykler / 6 = 266 666 => efter prescaler ( / 65535) = 4

start:
	jmp loop
loop: 	cpi third, <det värdet vi vill ha> 	; 1 cycle
	breq end				; 2 cycle	
	inc first	; 1 ; increment:ar första registret. Om overflow, incrementera andra reg.
	brvc loop       ; 2
	inc second	; 1 ; increment:ar andra registret. Om overflow, incrementera tredje reg.
	brvc loop	; 2
	inc third	; 1
	jmp loop	; 3
end:
	jmp end
```

## 1.5

```
#define PINB 0x03
#define DDRB 0x04
#define PORTB 0x05

start:
	ldi r18, 0b00010000 	; 
	out DDRB, r18 		; set data direction of LED2 as output
	out PORTB, r18

end:				; infinite looop
	rjmp end
```


## 2.1

```
; How do you allocate 10 integers on the stack?

#define N_ALLOC 20 	; 10 integers á 2 bytes
#define STACK_H 0x40FF
#define STACK_L 0x40FE

start:
	.
	.
	.

subroutine:
	;============== prologue beginning
	push r30 		; save where contents of Z(tack) reg.
	push r31
	in r30, STACK_L		; tmp store old stack pointer
	in r31, STACK_H
	sbiw Z, N_ALLOC
	out STACK_L, r30
	out STACK_H, r31 ; kanelbulle did not test this though
	;============== prologue ending

	.
	.
	.
	; We can also just move the stack pointer.
```

## 2.2

The difference of `0x40E0` and `0x40FF` is 32. The first element will be at address `0x40FF`, the
second element `0x40FE`, ..., index 3 will have address `0x40FC`

## 3.1

Man deklarerar en sub-rutin med en vanlig *label*, man behöver även avsluta med en `ret`. Sen för
att anropa använder man `call <subrutin>`.

## 3.2

*Argument* ligger i registerna och finns inte riktigt i Assembly(?). Om Assembly-kod används i ett
C-program så ligger de skickade argumenten i `r25` till `r8`. Resultatet som returneras kommer
ligga i registerna `r25` och `r24`. 

(Om subrutinen bara returnerar ett värde av 1 byte behöver man inte rensa `r25`)

## 3.3

```
0.35 µs * 16*10^6 Hz = 5,6 cykler  = 6
0.60 µs * 16*10^6 Hz = 9,6 cykler  = 10
0.70 µs * 16*10^6 Hz = 11,2 cykler = 11
0.80 µs * 16*10^6 Hz = 12,8 cykler = 13
50 µs * 16*10^6 Hz   = 800 cykler  = 800

```

## Skicka bits 


```
.global send_one
.global send_zero
.global send_ret

#define PORTD 0x0B
#define DDRD  0x0A

; cred till "AVR Delay loop calculator"

send_zero:
	; 0.35 us high
	; 0.80 us low
	ldi PORTD, 0b00010000 ; sets PIN 5 to high
	lpm		; 5 cycles, delay
	rjmp PC+1	; 5 cycles, delay 
	ldi PORTD, 0x00 ; sets PIN 5 to high
	ldi r18, 4	; 13 cycles, delay
L1:	dec r18		; 13 cycles, delay
	brne L1		; 13 cycles, delay
	nop		; 13 cycles, delay (kanske ska skippas.)

send_one:
	; 0.70 us high
	; 0.60 us low
	ldi PORTD, 0b00010000 ; sets PIN 5 to high
	lpm		; 10 cycles, delay
	lpm		; 10 cycles, delay
	lpm		; 10 cycles, delay
	nop		; 10 cycles, delay
	ldi PORTD, 0x00 ; 11th cycle
	lpm		; 10 cycles, delay
	lpm		; 10 cycles, delay
	lpm		; 10 cycles, delay
	nop		; 10 cycles, delay


send_ret:
	ldi r18, 2
	ldi r19, 9
L2:	dec r19
	brne L2
	dec r18
	brne L2

	
```
