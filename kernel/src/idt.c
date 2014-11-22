/* 
 * File:   idt.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include <kernel/descriptors.h>
#include <kernel/idt.h>
#include <kernel/mem.h>
#include <kernel/io.h>

/* ============================ Private constants =========================== */

#define IDT_ENTRY_NUM 256
#define IRQ_IDT_BASE 32

/* ============================ Private variables =========================== */

/* Array storing the IDT */
static struct idt_entry idt[IDT_ENTRY_NUM];

/* Pointer to the stored IDT */
static struct idt_ptr idt_p;

/* =========================== External functions =========================== */

extern void idt_flush (void *);

extern void _isr0  (void);
extern void _isr1  (void);
extern void _isr2  (void);
extern void _isr3  (void);
extern void _isr4  (void);
extern void _isr5  (void);
extern void _isr6  (void);
extern void _isr7  (void);
extern void _isr8  (void);
extern void _isr9  (void);
extern void _isr10 (void);
extern void _isr11 (void);
extern void _isr12 (void);
extern void _isr13 (void);
extern void _isr14 (void);
extern void _isr15 (void);
extern void _isr16 (void);
extern void _isr17 (void);
extern void _isr18 (void);
extern void _isr19 (void);
extern void _isr20 (void);
extern void _isr21 (void);
extern void _isr22 (void);
extern void _isr23 (void);
extern void _isr24 (void);
extern void _isr25 (void);
extern void _isr26 (void);
extern void _isr27 (void);
extern void _isr28 (void);
extern void _isr29 (void);
extern void _isr30 (void);
extern void _isr31 (void);

extern void _irq0  (void);
extern void _irq1  (void);
extern void _irq2  (void);
extern void _irq3  (void);
extern void _irq4  (void);
extern void _irq5  (void);
extern void _irq6  (void);
extern void _irq7  (void);
extern void _irq8  (void);
extern void _irq9  (void);
extern void _irq10 (void);
extern void _irq11 (void);
extern void _irq12 (void);
extern void _irq13 (void);
extern void _irq14 (void);
extern void _irq15 (void);

/* ============================ Private functions =========================== */

static void irq_remap (void)
{
	outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/* Initializes the gate of index id inside the IDT */
static void idt_set_gate (uint8_t id, uint32_t base, uint16_t sel, uint8_t flags)
{
	struct idt_entry *p_gate = &idt[id];

	p_gate->base_lo = (uint16_t)(base & 0xFFFF);
	p_gate->base_hi = (uint16_t)((base >> 16) & 0xFFFF);

	p_gate->sel   = sel;
	p_gate->rsvd0 = 0x0;
	p_gate->flags = flags;
}

/* ============================ Public functions ============================ */

/* Initializes and installs the IDT */
void idt_install (void)
{
	/* Set up IDT pointer */
	idt_p.base  = (uint32_t) &idt;
	idt_p.limit = (IDT_ENTRY_NUM * sizeof(struct idt_entry)) - 1;

	/* Zero entire table */
	kmemset((void *) idt_p.base, 0x0, (IDT_ENTRY_NUM * sizeof(struct idt_entry)));

	/* Remap PIC to IDT gates 31 and above */
	irq_remap();

	idt_set_gate (0 , (uint32_t) _isr0 , 0x08, 0x8E);
	idt_set_gate (1 , (uint32_t) _isr1 , 0x08, 0x8E);
	idt_set_gate (2 , (uint32_t) _isr2 , 0x08, 0x8E);
	idt_set_gate (3 , (uint32_t) _isr3 , 0x08, 0x8E);
	idt_set_gate (4 , (uint32_t) _isr4 , 0x08, 0x8E);
	idt_set_gate (5 , (uint32_t) _isr5 , 0x08, 0x8E);
	idt_set_gate (6 , (uint32_t) _isr6 , 0x08, 0x8E);
	idt_set_gate (7 , (uint32_t) _isr7 , 0x08, 0x8E);
	idt_set_gate (8 , (uint32_t) _isr8 , 0x08, 0x8E);
	idt_set_gate (9 , (uint32_t) _isr9 , 0x08, 0x8E);
	idt_set_gate (10, (uint32_t) _isr10, 0x08, 0x8E);
	idt_set_gate (11, (uint32_t) _isr11, 0x08, 0x8E);
	idt_set_gate (12, (uint32_t) _isr12, 0x08, 0x8E);
	idt_set_gate (13, (uint32_t) _isr13, 0x08, 0x8E);
	idt_set_gate (14, (uint32_t) _isr14, 0x08, 0x8E);
	idt_set_gate (15, (uint32_t) _isr15, 0x08, 0x8E);
	idt_set_gate (16, (uint32_t) _isr16, 0x08, 0x8E);
	idt_set_gate (17, (uint32_t) _isr17, 0x08, 0x8E);
	idt_set_gate (18, (uint32_t) _isr18, 0x08, 0x8E);
	idt_set_gate (19, (uint32_t) _isr19, 0x08, 0x8E);
	idt_set_gate (20, (uint32_t) _isr20, 0x08, 0x8E);
	idt_set_gate (21, (uint32_t) _isr21, 0x08, 0x8E);
	idt_set_gate (22, (uint32_t) _isr22, 0x08, 0x8E);
	idt_set_gate (23, (uint32_t) _isr23, 0x08, 0x8E);
	idt_set_gate (24, (uint32_t) _isr24, 0x08, 0x8E);
	idt_set_gate (25, (uint32_t) _isr25, 0x08, 0x8E);
	idt_set_gate (26, (uint32_t) _isr26, 0x08, 0x8E);
	idt_set_gate (27, (uint32_t) _isr27, 0x08, 0x8E);
	idt_set_gate (28, (uint32_t) _isr28, 0x08, 0x8E);
	idt_set_gate (29, (uint32_t) _isr29, 0x08, 0x8E);
	idt_set_gate (30, (uint32_t) _isr30, 0x08, 0x8E);
	idt_set_gate (31, (uint32_t) _isr31, 0x08, 0x8E);

	idt_set_gate(IRQ_IDT_BASE + 0 , (uint32_t) _irq0 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 1 , (uint32_t) _irq1 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 2 , (uint32_t) _irq2 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 3 , (uint32_t) _irq3 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 4 , (uint32_t) _irq4 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 5 , (uint32_t) _irq5 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 6 , (uint32_t) _irq6 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 7 , (uint32_t) _irq7 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 8 , (uint32_t) _irq8 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 9 , (uint32_t) _irq9 , 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 10, (uint32_t) _irq10, 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 11, (uint32_t) _irq11, 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 12, (uint32_t) _irq12, 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 13, (uint32_t) _irq13, 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 14, (uint32_t) _irq14, 0x08, 0x8E);
	idt_set_gate(IRQ_IDT_BASE + 15, (uint32_t) _irq15, 0x08, 0x8E);

	/* Register IDT with the processor */
	idt_flush((void *) &idt_p);
}
