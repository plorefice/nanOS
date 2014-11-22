[BITS 32]

; Declare constants used for creating a multiboot header.
MBALIGN     equ 1<<0                 ; align loaded modules on page boundaries
MBMEMINFO   equ 1<<1                 ; provide memory map
MBFLAGS     equ MBALIGN | MBMEMINFO  ; this is the Multiboot 'flag' field
MBMAGIC     equ 0x1BADB002           ; lets bootloader find the header
MBCHECKSUM  equ -(MBMAGIC + MBFLAGS) ; checksum to prove multiboot

; BEGIN .MULTIBOOT =========================================================== ;
[SECTION .multiboot]

; Declare multiboot header section
align 4
dd MBMAGIC
dd MBFLAGS
dd MBCHECKSUM

; BEGIN .BOOTSTRAP_STACK ===================================================== ;
[SECTION .bootstrap_stack]

; Reserve 16KB bootstrap stack
stack_bottom:
times 16384 db 0
stack_top:

; BEGIN .TEXT ================================================================ ;
[SECTION .text]

; ------------ Kernel entry point ----------- ;
[GLOBAL _start]
[EXTERN kmain]
_start:
	; Start with disabled interrupts
	cli

	; Initialize stack pointer
	mov esp, stack_top

	; Transfer control to kmain
	call kmain
	
	; Hang if kmain unexpectedly returns.
	cli
	hlt

.Lhang:
	hlt
	jmp .Lhang


; Chech A20 gate
[GLOBAL a20_enabled]
a20_enabled:
	pushf

	cli

.waitcmd1:
	xor ax, ax
	in  al, 64h
	bt  ax, 1
	jc  .waitcmd1

	; Issue read output port command
	mov al, 0D0h
	out 64h, al

.waitst1:
	xor ax, ax
	in  al, 64h
	bt  ax, 0
	jnc .waitst1

	; Read ouput port
	xor ax, ax
	in  al, 60h

	; Check A20 bit
	bt ax, 1
	jc .success 

	mov al, 0
	jmp .done

.success:
	mov al, 1

.done:
	popf
	ret

; --------------------- GDT --------------------- ;
[GLOBAL gdt_flush]
gdt_flush:
	mov  eax, [esp+4]
	lgdt [eax]
	mov  ax, 0x10
	mov  ds, ax
	mov  es, ax
	mov  fs, ax
	mov  gs, ax
	mov  ss, ax
	jmp  0x08:.flush
.flush:
	ret

; --------------------- IDT --------------------- ;
[GLOBAL idt_flush]
idt_flush:
	mov  eax, [esp+4]
	lidt [eax]
	ret
