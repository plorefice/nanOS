/* 
 * File:   heap.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_HEAP_H
#define __KERNEL_HEAP_H

#include <stddef.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

void * kmalloc    (size_t sz);
void * kmalloc_a  (size_t sz);
void * kmalloc_p  (size_t sz, uintptr_t *phys);
void * kmalloc_ap (size_t sz, uintptr_t *phys);

#endif /* __KERNEL_HEAP_H */