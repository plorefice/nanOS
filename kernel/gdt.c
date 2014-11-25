/* 
 * File:   gdt.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include <kernel/gdt.h>
#include <kernel/descriptors.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

/* Array storing the GDT */
static struct gdt_entry gdt[5];

/* Pointer to the stored GDT */
static struct gdt_ptr gdt_p;

/* =========================== External functions =========================== */

extern void gdt_flush (void *);

/* ============================ Private functions =========================== */

/* Initializes the gate of index id inside the GDT */
static void gdt_set_gate (uint8_t  id, 
                          uint32_t base,
                          uint32_t limit,
                          uint8_t  access,
                          uint8_t  flags)
{
	struct gdt_entry *p_gate = &gdt[id];

	p_gate->base_low  = (uint16_t)(base & 0xFFFF);
	p_gate->base_mid  = (uint8_t)((base >> 16) & 0xFF);
	p_gate->base_high = (uint8_t)((base >> 24) & 0xFF);

	p_gate->limit_low  = (uint16_t)(limit & 0xFFFF);
	p_gate->limit_high = (uint8_t)((limit >> 16) & 0x0F);

	p_gate->flags = flags & 0x0F;

	p_gate->access = access;
}

/* ============================ Public functions ============================ */

/* Initializes and installs the GDT */
void gdt_install (void)
{
	gdt_p.base  = (uint32_t) &gdt;
	gdt_p.limit = (5 * sizeof(struct gdt_entry)) - 1;

	gdt_set_gate(0, 0, 0, 0, 0);             /* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0x0C); /* Ring-0 code segment */
	gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0x0C); /* Ring-0 data segment */
	gdt_set_gate(3, 0, 0xFFFFF, 0xFA, 0x0C); /* Ring-3 code segment */
	gdt_set_gate(4, 0, 0xFFFFF, 0xF2, 0x0C); /* Ring-3 data segment */

	/* Load new GDT */
	gdt_flush((void *) &gdt_p);
}
