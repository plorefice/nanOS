[BITS 32]

; BEGIN .DATA ================================================================ ;
[SECTION .data]

ALIGN 0x1000
_kernel_pd:
	times 1024 dd 0  ; kernel page-directory
_kernel_hi_pt:
	times 1024 dd 0  ; kernel page-table (mapping to higher half)
_kernel_lo_pt:
	times 1024 dd 0  ; kernel page-table (mapping to lower half)

_msg_panic:
	db 'PANIC!',0     ; null-terminated string


; BEGIN .BSS ================================================================ ;
[SECTION .bss]

ALIGN 4
_bootstack_bottom:
	resb 16384      ; 16K boot stack
_bootstack_top:


; BEGIN .BOOT ================================================================ ;
[SECTION .boot]

; Declare constants used for creating a multiboot header.
MBALIGN     equ 1<<0                 ; align loaded modules on page boundaries
MBMEMINFO   equ 1<<1                 ; provide memory map
MBFLAGS     equ MBALIGN | MBMEMINFO  ; this is the Multiboot 'flag' field
MBMAGIC     equ 0x1BADB002           ; lets bootloader find the header
MBCHECKSUM  equ -(MBMAGIC + MBFLAGS) ; checksum to prove multiboot

; Declare multiboot header section
ALIGN 4
dd MBMAGIC
dd MBFLAGS
dd MBCHECKSUM

; Declare useful symbols
VIDEO_MEM      equ 0xB8000
VIDEO_WD_COUNT equ 0x7D0

; ------------ Kernel entry point ----------- ;
[EXTERN KERNEL_VMA_OFFSET]
[EXTERN __boot_start]
[EXTERN __boot_end]
[EXTERN __kernel_start]
[EXTERN __kernel_end]
[EXTERN kmain]

[GLOBAL _bootstrap]
_bootstrap:
	cli                           ; Start with interrupts disabled

	mov esp, _bootstack_top       ; Set esp to point to the top of the stack
	sub esp, KERNEL_VMA_OFFSET    ; Adjust esp to match the PHYSICAL address
	                              ; of the stack (.data is at 0xC0000000)

	call _boot_setup_paging       ; Where the magic happens

	        ; From this moment on, paging is enabled! ;

	push eax                      ; Save eax
	mov  edi, VIDEO_MEM           ; Test lower-half paging by
	mov  ecx, VIDEO_WD_COUNT      ; Trying to blank video memory
	mov  eax, 0x0720              ; 0x0720 = whitespaces (light-grey on black)
	rep  stosw
	pop  eax                      ; Restore eax

	push eax                      ; Pass GRUB multiboot informations to
	push ebx                      ; the entry point
	call kmain                    ; Transfer control to C entry-point

	jmp _bootstrap_end

	cli                           ; Unexpected termination: hang!
	hlt
.hang:
	hlt
	jmp .hang


; Test whether pagign was enabled successfully
_bootstrap_end:
	mov eax, _msg_panic           ; Pass string to _boot_print_msg

	call _boot_print_msg          ; Print string

	cli                           ; Halt
	hlt


; Print test message on the screen
_boot_print_msg:
	push edi
	push esi
	push ebx

	mov edi, VIDEO_MEM      ; vm = 0x8B000
	mov esi, eax            ; _msg_panic = ...

	xor bx, bx
	or  bx, 0x0700
.loop:
	mov bl, [esi]
	cmp bl, 0x0             ; while (*(_msg_panic) != 0)
	je  .end                ; {
	mov [edi], bx           ;   *(vm) = c;
	add edi, 2              ;   vm++;
	inc esi                 ;   _msg_panic++;
	jmp .loop               ; }

.end:
	pop ebx
	pop esi
	pop edi
	ret


; Again, where the magic happens...
_boot_setup_paging:
	pusha                        ; Save everything to be safe

	mov eax, _kernel_pd          ; Load VIRTUAL page-directory address
	sub eax, KERNEL_VMA_OFFSET   ; Translate into PHYSICAL address

	mov ebx, _kernel_lo_pt       ; Load VIRTUAL lower page-table address
	sub ebx, KERNEL_VMA_OFFSET   ; Translate into PHYSICAL address

	or  ebx, 0x1                 ; Set present flag
	mov [eax], ebx               ; Set PDE #0x0 to point to the lower page-table

	mov ebx, _kernel_hi_pt       ; Load VIRTUAL higher page-table address
	sub ebx, KERNEL_VMA_OFFSET   ; Translate into PHYSICAL address

	mov ecx, KERNEL_VMA_OFFSET   ; Tricky part: find PDE corresponding to
	                             ; higher-half page-table
	shr ecx, 22                  ; To do it, we take the first 10-bit of the VM
	or  ebx, 0x1                 ; offset, and we use them as index to access
	mov [eax + ecx * 4], ebx     ; the page-directory

	                             ; PDE correctly filled!

	mov ecx, 0x00100000          ; On to the mapping!
.idmap_lo_1mb:                   ; Identity-map the first 1MiB
	push ecx                     ; arg[2] = paddr
	push ecx                     ; arg[1] = vaddr
	push eax                     ; arg[0] = pd
	call _boot_map_page          ; _boot_map_page(pd, vaddr, paddr)
	add  esp, 12                 ; Clean stack
	sub  ecx, 0x1000             ; Map previous page
	jnz .idmap_lo_1mb


	mov ecx, __boot_end
	mov ebx, __boot_start
.idmap_boot:                     ; Identity-map the .boot section
	push ecx,
	push ecx,
	push eax,
	call _boot_map_page
	add  esp, 12
	sub  ecx, 0x1000
	cmp  ecx, ebx
	jge .idmap_boot

	mov ecx, __kernel_end
	sub ecx, KERNEL_VMA_OFFSET

	mov ebx, __kernel_start
	sub ebx, KERNEL_VMA_OFFSET
.map_kernel:                     ; Map kernel to higher-half
	push ecx

	mov  edx, ecx
	add  edx, KERNEL_VMA_OFFSET
	push edx

	push eax
	call _boot_map_page
	add  esp, 12
	sub  ecx, 0x1000
	cmp  ecx, ebx
	jge .map_kernel

	mov cr3, eax
	mov eax, cr0
	or  eax, 0x80000000
	mov cr0, eax

	add esp, KERNEL_VMA_OFFSET   ; IMPORTANT: translate esp to VIRTUAL address
	                             ; before performing push/pop operations

	popa                         ; Restore everything to be safe
	ret


; void _boot_map_page (void *pd, void *vaddr, void *paddr)
; pd    : page-directory address
; vaddr : virtual address to map
; paddr : physical address to map to
_boot_map_page:
	push ebp                   ; Save previous context
	mov  ebp, esp              ; Load new context

	pusha

	mov ebx, [ebp+12]
	mov ecx, ebx
	shr ebx, 12                
	and ebx, 0x003FF           ; EBX = PTE index
	shr ecx, 22                ; ECX = PDE index

	mov esi, [ebp+8]           ; NB: simplified assumption that the PDE actually
	mov edi, [esi + ecx*4]     ;     contains the address of a page-table
	and edi, 0xFFFFF000        ; EDI = page-table address

	mov esi, [ebp+16]
	and esi, 0xFFFFF000        ; ESI = paddr
	or  esi, 0x1               ; Set P flag
	mov [edi + ebx*4], esi     ; Set PTE entry

	popa

	pop ebp                    ; Restore previously saved context
	ret
