/* 
 * File:   pit.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_PIT_H
#define __KERNEL_PIT_H

#include <stdint.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

void timer_wait     (uint32_t ticks);
void timer_set_freq (uint32_t freq);
void timer_install  (void);

#endif /* __KERNEL_PIT_H */