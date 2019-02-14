# 1.4
* 1.1
```
start:
	ldi r16, 3
	ldi r17, 4
	add r17, r16
```

* 1.2
```
start:
	cpi r16, 18
	brge one 	; if Greater or Equal.
	brlt two	; if Less Than.

one:
	ldi r24, 1
	jmp end

two:
	ldi r24, 2
	jmp end

end:			; Infinite loop
	rjmp end	
```

* 1.3
```
#define PINB 0x03
#define DDRB 0x04
#define PORTB 0x05

start:
	ldi r18, 0xFF
	out DDRB, r18 	; set LED0 as output
end:
	in PORTB, PINB
	rjmp end ; infinite loop
```

# 1.4
```
; input ligger i r20.
; a ligger i r24
start:
	cpi r24, 12	
	brlt lt
	breq equals
	
	ldi r24, 5	; "else"

lt:			; less than 12
	ldi r24, 3
	jmp end
equals:			; equals 12
	ldi r24, 2
	jmp end

end:			; Infinite loop
	rjmp end	
```

# 1.5
```
; msg 	  ligger i r16
; msg_end ligger i r24

start:
	ldi r24, r16
	<fooor loop>
		shr 		
```
