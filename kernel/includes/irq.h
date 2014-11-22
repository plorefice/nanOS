/* 
 * File:   irq.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_IRQ_H
#define __KERNEL_IRQ_H

#include <stdint.h>

#include <kernel/descriptors.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

typedef void (*isr_t)(struct cpu_state *);

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

void irq_install_handler   (uint16_t id, isr_t handler);
void irq_uninstall_handler (uint16_t id);
void irq_enable            (void);
void irq_disable           (void);

#endif /* __KERNEL_IRQ_H */
