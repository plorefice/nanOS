/* 
 * File:   mem.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_COMMON_H
#define __KERNEL_COMMON_H

#include <stddef.h>
#include <stdint.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

int     kmemcmp  (const void *ptr1, const void *ptr2, size_t num);
void   *kmemcpy  (void *dst, const void *src, size_t num);
void   *kmemmove (void *dst, const void *src, size_t num);
void   *kmemset  (void *dst, int val, size_t num);
void   *kmemsetw (void *dst, int val, size_t num);
size_t  kstrlen  (const char *s);

#endif /* __KERNEL_COMMON_H */
