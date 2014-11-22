/* 
 * File:   idt.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_IDT_H
#define __KERNEL_IDT_H

#include <stdint.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

void idt_install  (void);

#endif /* __KERNEL_IDT_H */