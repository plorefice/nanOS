/* 
 * File:   heap.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include <kernel/heap.h>

/* ============================ Private constants =========================== */

extern uintptr_t _kend;

/* ============================ Private variables =========================== */

uintptr_t placement_addr = (uintptr_t)&_kend;

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static void *_kmalloc (size_t sz, uint8_t align, uintptr_t *phys)
{
	uintptr_t ptr;

	if (align && (placement_addr & 0x00000FFF))
	{
		placement_addr &= 0xFFFFF000;
		placement_addr += 0x1000;
	}

	if (phys)
	{
		*phys = placement_addr;
	}
	
	ptr = placement_addr;
	placement_addr += sz;
	return (void *) ptr;
}

/* ============================ Public functions ============================ */

void * kmalloc (size_t sz)
{
	return _kmalloc(sz, 0, 0);
}

void * kmalloc_a (size_t sz)
{
	return _kmalloc(sz, 1, 0);
}

void * kmalloc_p (size_t sz, uintptr_t *phys)
{
	return _kmalloc(sz, 0, phys);
}

void * kmalloc_ap (size_t sz, uintptr_t *phys)
{
	return _kmalloc(sz, 1, phys);
}
