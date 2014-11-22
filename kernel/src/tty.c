/* 
 * File:   tty.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/io.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

static size_t    tty_row;
static size_t    tty_column;
static uint8_t   tty_color;
static uint16_t *tty_buffer;

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static void tty_updatecur (void)
{
	uint16_t pos = tty_row * VGA_WIDTH + tty_column;

	outportb(0x3D4, 0x0F);
	outportb(0x3D5, pos & 0xFF);
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (pos >> 8) & 0xFF);
}

/* ============================ Public functions ============================ */

void tty_init (void)
{
	tty_row    = 0;
	tty_column = 0;
	tty_color  = vga_make_color(LIGHT_GREY, BLACK);
	tty_buffer = (uint16_t *) VGA_MEMORY;

	tty_cls();
}

void tty_cls (void)
{
	size_t i;

	for (i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++)
		tty_buffer[i] = vga_entry(' ', tty_color);
	
	tty_row    = 0;
	tty_column = 0;
}

void tty_scroll (void)
{
	if (tty_row >= VGA_HEIGHT)
	{
		size_t l24 = (VGA_HEIGHT - 1) * VGA_WIDTH;
		size_t l25 = VGA_HEIGHT * VGA_WIDTH;
		size_t i;

		for (i = 0; i < l24; i++)
			tty_buffer[i] = tty_buffer[i + VGA_WIDTH];

		for (i = l24; i < l25; i++)
			tty_buffer[i] = vga_entry(' ', tty_color);

		tty_row = VGA_HEIGHT - 1;
	}
}

void tty_set_color (enum vga_color fg, enum vga_color bg)
{
	tty_color = vga_make_color(fg, bg);
}

void tty_putc (char c)
{
	const size_t idx = tty_row * VGA_WIDTH + tty_column;

	switch (c)
	{
	case '\n': goto newline;
	case '\r': goto linefeed;
	case '\b': goto backspace;
	default  : goto print;
	}

print:
	tty_buffer[idx] = vga_entry(c, tty_color);

	if (tty_column == VGA_WIDTH - 1)
		goto newline;
	else
		tty_column++;

	goto done;

newline:
	tty_row++;
	tty_scroll();

linefeed:
	tty_column = 0;
	goto done;

backspace:
	if (tty_column != 0) tty_column--;
	goto done;

done:
	tty_updatecur();
	return;
}

int tty_putstr (const char *s)
{
	size_t t   = 0;

	while (s[t])
		tty_putc(s[t++]);

	return (int) t;
}
