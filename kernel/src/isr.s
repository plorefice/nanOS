[BITS 32]

; --------------------- ISR --------------------- ;
%macro ISR_ERRCODE 1
	[GLOBAL _isr%1]
	_isr%1:
		cli
		push dword %1  ; ISR identifier
		jmp _isr_common_stub
%endmacro

%macro ISR_NOERRCODE 1
	[GLOBAL _isr%1]
	_isr%1:
		cli
		push dword 0h  ; Dummy error code
		push dword %1  ; ISR identifier
		jmp _isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31


[GLOBAL _isr_common_stub]
[EXTERN isr_handler]
_isr_common_stub:
	pusha               ; Save processor state

	push ds             ; Save segment selectors
	push es 
	push fs
	push gs
	mov  ax, 0x10       ; Switch to kernel data segment
	mov  ds, ax
	mov  es, ax
	mov  fs, ax
	mov  gs, ax

	mov  eax, esp       ; Pass execution trace to fault_handler
	push eax
	call isr_handler
	pop  eax

	pop  gs             ; Restore segment selectors
	pop  fs
	pop  es
	pop  ds
	popa                ; Restore processor state
	add  esp, 8         ; Remove error code and ISR id
	iret

; --------------------- IRQ --------------------- ;
%macro IRQ 1
	[GLOBAL _irq%1]
	_irq%1:
		cli
		push dword 0h     ; Dummy error code
		push dword 32+%1  ; IRQ identifier (32 + i)
		jmp _irq_common_stub
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15


[GLOBAL _irq_common_stub]
[EXTERN irq_handler]
_irq_common_stub:
	pusha               ; Save processor state

	push ds             ; Save segment selectors
	push es 
	push fs
	push gs
	mov  ax, 0x10       ; Switch to kernel data segment
	mov  ds, ax
	mov  es, ax
	mov  fs, ax
	mov  gs, ax

	mov  eax, esp       ; Pass execution trace to irq_handler
	push eax
	call irq_handler
	pop  eax

	pop  gs             ; Restore segment selectors
	pop  fs
	pop  es
	pop  ds
	popa                ; Restore processor state
	add  esp, 8         ; Remove error code and ISR id
	iret
