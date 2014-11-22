/* 
 * File:   tty.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_TTY_H
#define __KERNEL_TTY_H

#include <kernel/vga.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

void tty_init      (void);
void tty_cls       (void);
void tty_scroll    (void);
void tty_set_color (enum vga_color fg, enum vga_color bg);

void tty_putc      (char c);
int  tty_putstr    (const char *s);

#endif /* __KERNEL_TTY_H */