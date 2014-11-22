/* 
 * File:   descriptors.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_DESCRIPTORS_H
#define __KERNEL_DESCRIPTORS_H

#include <stdint.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* Defines a GDT entry */
struct gdt_entry
{
	uint16_t limit_low  :16;
	uint16_t base_low   :16;
	uint8_t  base_mid   :8;
	uint8_t  access     :8;
	uint8_t  limit_high :4;
	uint8_t  flags      :4;
	uint8_t  base_high  :8;
} __attribute__((packed));


/* Defines a GDT pointer */
struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));


/* Defines an IDT entry */
struct idt_entry
{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t  rsvd0;
	uint8_t  flags;
	uint16_t base_hi;
} __attribute__((packed));

/* Defines an IDT pointer */
struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));


/* Describes the last known processor state */
struct cpu_state
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_no;
	uint32_t eip, cs, eflags, uesp, ss;
};


/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

#endif /* __KERNEL_DESCRIPTORS_H */
