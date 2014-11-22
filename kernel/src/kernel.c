#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/kbd.h>
#include <kernel/heap.h>
#include <kernel/paging.h>

extern uint8_t a20_enabled (void);

void kmain (void)
{
	tty_init();

	kprintf("nanOS v0.0.1 - libc v0.0.1\n");

	kprintf("\n[-] Setting up virtual memory...\n");

		kprintf(" |-[+] Installing GDT... ");
		gdt_install();
		kprintf("Done.\n");

		kprintf(" |-[+] Installing IDT... ");
		idt_install();
		kprintf("Done.\n");

		kprintf(" |-[+] Enabling paging... ");
		paging_init();
		kprintf("Done.\n");


	kprintf("\n[-] Installing IRQs...\n");
		kprintf(" |-[+] Timer... ");
		timer_install();
		kprintf("Done.\n");

		kprintf(" |-[+] Keyboard... ");
		kb_install();
		kprintf("Done.\n");
		

	kprintf("\n[-] Enabling IRQs... ");
		irq_enable();
		kprintf("Done.\n");


	volatile uint32_t *ptr = (uint32_t *) 0xA0000000;
	volatile uint32_t  p = *ptr;

	for (;;) ;
}
