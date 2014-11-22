/* 
 * File:   gdt.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_GDT_H
#define __KERNEL_GDT_H

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */
 
void gdt_install (void);

#endif /* __KERNEL_GDT_H */