/* 
 * File:   io.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_IO_H
#define __KERNEL_IO_H

#include <stdint.h>

#include <kernel/descriptors.h>

/* =========================== Exported constants =========================== */

#define PANIC(msg, cpu) (kpanic(msg, cpu, __FILE__, __LINE__))

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

static inline void outportb (uint16_t port, uint8_t data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "d" (port), "a" (data));
}


static inline uint8_t inportb (uint16_t port)
{
	uint8_t val;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (val) : "d" (port));
	return val;
}

void kputc   (int c);
int  kprintf (const char *ftm, ...);
void kpanic  (const char *s, struct cpu_state *cpu, const char *fn, int line);

#endif /* __KERNEL_IO_H */