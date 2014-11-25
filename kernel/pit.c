/* 
 * File:   pit.c
 * Author: Pietro Lorefice
 */

#include <kernel/pit.h>
#include <kernel/io.h>
#include <kernel/irq.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

static volatile uint32_t ticks = 0;

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static void timer_handler (struct cpu_state *cpu __attribute__((unused)))
{
	ticks++;
}

/* ============================ Public functions ============================ */

void timer_wait (uint32_t t)
{
	uint64_t end = ticks + t;

	while (ticks < end) ;
}

void timer_set_freq (uint32_t freq)
{
	uint16_t fdiv = 1193182 / freq;

	outportb(0x43, 0x36);
	outportb(0x40, fdiv & 0xFF);
	outportb(0x40, (fdiv >> 8) & 0xFF);
}

void timer_install (void)
{
	timer_set_freq(100);
	irq_install_handler(32, timer_handler);
}
