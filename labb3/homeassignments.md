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

loop:
	; Kollar om vårt värde är nått i register 3.
	cpi third, <det värdet vi vill ha> 	; 1 cycle
	breq end				; 2 cycle	
	
	; increment:ar första registret. Om overflow, incrementera andra reg.
	inc first	; 1
	brvc loop       ; 2
	
	; increment:ar andra registret. Om overflow, incrementera tredje reg.
	inc second	; 1
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
	out STACK_H, r31
	;============== prologue ending

	.
	.
	.
```

## 2.2

The difference of `0x40E0` and `0x40FF` is 32. The first element will be at address `0x40FF`, the
second element `0x40FE`, ..., index 3 will have address `0x40FC`
