#include <kernel/io.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/pit.h>
#include <kernel/kbd.h>
#include <kernel/heap.h>

#include <drivers/serial.h>

static const char *serial_test = "String longer than 16 bytes to test overflow";

void kmain (void)
{
	tty_init();

	kprintf("nanOS v0.0.1 - libc v0.0.1\n");
	kprintf("\n");

	kprintf("[-] Installing GDT... ");
	gdt_install();
	kprintf("Done.\n");
	
	kprintf("[-] Installing IDT... ");
	idt_install();
	kprintf("Done.\n");
	
	kprintf("[-] Installing IRQs...\n");
	kprintf(" |-[+] Timer... ");
	timer_install();
	kprintf("Done.\n");
	
	kprintf(" |-[+] Keyboard... ");
	kb_install();
	kprintf("Done.\n");
	
	kprintf("[-] Enabling IRQs... ");
	irq_enable();
	kprintf("Done.\n");


	{   /* Serial port test */

		struct serial_config com1_config = 
			{
				.baud_rate   = 9600,
				.break_bit   = SERIAL_BREAK_DISABLED,
				.parity_bit  = SERIAL_PARITY_NONE,
				.stop_bit    = SERIAL_STOP_1,
				.word_length = SERIAL_WLEN_8,
			};

		serial_set_config(1, &com1_config);
		serial_set_fifo_config(1);

		serial_write(1, serial_test, 44);
	}


	for (;;) ;
}
