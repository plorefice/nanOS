# CFLAGS for module
CFLAGS_kernel  := -ffreestanding -Wall -Wextra -Wno-packed-bitfield-compat
ASFLAGS_kernel := 
LDFLAGS_kernel := -nostdlib -lgcc

# Executable to build in module
kernel_PROGRAM := kernel

# Libraries that the executable depends on:
kernel_LIBRARIES :=

# Sources for the executable (without headers)
kernel_SOURCES := \
	kernel.c \
	boot.s   \
	         \
	gdt.c    \
	heap.c   \
	idt.c    \
	io.c     \
	irq.c    \
	isr.s    \
	kbd.c    \
	mem.c    \
	paging.c \
	pit.c    \
	tty.c    \
