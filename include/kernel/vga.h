/* 
 * File:   vga.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_VGA_H
#define __KERNEL_VGA_H

#include <stdint.h>

/* =========================== Exported constants =========================== */

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static uint16_t * const VGA_MEMORY = (uint16_t *) 0xC00B8000;

/* ============================= Exported types ============================= */

enum vga_color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

static inline uint8_t vga_make_color (enum vga_color fg, enum vga_color bg)
{
	return (bg << 4) | fg;
}

static inline uint16_t vga_entry (char c, uint8_t attrib)
{
	uint16_t c16 = c;
	uint16_t a16 = attrib << 8;
	return a16 | c16;
}

#endif /* __KERNEL_VGA_H */
