/* 
 * File:   kbd.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include <kernel/kbd.h>
#include <kernel/irq.h>
#include <kernel/io.h>

/* ============================ Private constants =========================== */

#define KB_ALT      (0x0001)
#define KB_CTRL     (0x0002)
#define KB_SHIFT    (0x0004)
#define KB_CAPS_LCK (0x0008)
#define KB_NUM_LCK  (0x0010)
#define KB_SCR_LCK  (0x0020)

/* ============================ Private variables =========================== */

static uint16_t flags = 0;

static unsigned char kbdus[256] =
{
	[0] = /* lower-case character set */

	   0,    0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',  '-', '=',
	'\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
	'\n',    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	   0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*', 
	   0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
	   0,  '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',  '0', '.',
	   0,    0,   0,   0,   0,

	[128] = /* upper-case character set */

	   0,    0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',  '_', '+',
	'\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '{', '}',
	'\n',    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',  '"', '~',
	   0,  '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',    0, '*', 
	   0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
	   0,  '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',  '0', '.',
	   0,    0,   0,   0,   0
};

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static void kb_handler (struct cpu_state *cpu __attribute__((unused)))
{
	uint8_t scancode = inportb(0x60);

	if (scancode & 0x80) /* Key released */
	{
		switch (scancode & 0x7F)
		{
		case 0x1D:
			flags &= ~KB_CTRL;
			break;
		case 0x2A:
		case 0x36:
			flags &= ~KB_SHIFT;
			break;
		case 0x38:
			flags &= ~KB_ALT;
			break;
		default:
			break;
		}
	}
	else /* Key pressed */
	{
		switch (scancode)
		{
		case 0x1D:
			flags |= KB_CTRL;
			break;
		case 0x2A:
		case 0x36:
			flags |= KB_SHIFT;
			break;
		case 0x38:
			flags |= KB_ALT;
			break;

		case 0x3A:
			flags ^= KB_CAPS_LCK;
			break;
		case 0x45:
			flags ^= KB_NUM_LCK;
			break;
		case 0x46:
			flags ^= KB_SCR_LCK;
			break;
		default:
			break;
		}

		if (kbdus[scancode] != 0)
		{
			uint8_t idx = (flags & (KB_SHIFT | KB_CAPS_LCK)) ? 
				scancode + 0x80 : scancode;

			kputc(kbdus[idx]);
		}
	}
}

/* ============================ Public functions ============================ */

void kb_install (void)
{
	irq_install_handler(33, kb_handler);
}
