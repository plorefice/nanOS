/* 
 * File:   irq.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/io.h>
#include <kernel/descriptors.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

static isr_t interrupt_handlers[256] = { 0 };

/* Exception messages printed by the fault handler */
static const char * const exception_messages[] =
{
	"Division By Zero", 
	"Debug", 
	"Non Maskable Interrupt", 
	"Breakpoint", 
	"Into Detected Overflow", 
	"Out of Bounds", 
	"Invalid Opcode", 
	"No Coprocessor", 
	"Double Fault", 
	"Coprocessor Segment Overrun", 
	"Bad TSS", 
	"Segment Not Present", 
	"Stack Fault", 
	"General Protection Fault", 
	"Page Fault", 
	"Unknown Interrupt", 
	"Coprocessor Fault", 
	"Alignment Check", 
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

/* Handles fault and internal interruptions */
void isr_handler (struct cpu_state *cpu)
{
	isr_t handler = interrupt_handlers[cpu->int_no];

	if (handler) {
		/* Handle exception */
		handler(cpu);
	}
	else
	{
		/* Unhandled exception: kernel panic */
		PANIC(exception_messages[cpu->int_no], cpu);
	}

	for (;;) ;	
}

/* Handles external interrupts */
void irq_handler (struct cpu_state *cpu)
{
	isr_t handler = interrupt_handlers[cpu->int_no];

	/* Send EOI configuration to slave PIC */
	if (cpu->int_no >= 40)
		outportb(0xA0, 0x20);

	/* Send EOI configuration to master PIC anyway */
	outportb(0x20, 0x20);

	/* Handle interrupt, if registered */
	if (handler)
		handler(cpu);
}

/* ============================ Public functions ============================ */

void irq_install_handler (uint16_t id, isr_t handler)
{
	interrupt_handlers[id] = handler;
}

void irq_uninstall_handler (uint16_t id)
{
	interrupt_handlers[id] = 0;
}

void irq_enable (void)
{
	__asm__ __volatile__ ("sti");
}

void irq_disable (void)
{
	__asm__ __volatile__ ("cli");
}
