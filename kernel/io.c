/* 
 * File:   io.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>
#include <stdarg.h>

#include <kernel/io.h>
#include <kernel/vga.h>
#include <kernel/tty.h>

/* ============================ Private constants =========================== */

/* ============================ Private variables =========================== */

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static int kprint_int (int d)
{
	int rem = 0, n = 0, ret = 0;
	char buff[64];

	if (d < 0)
	{
		d = -d;
		tty_putc('-');
		ret++;
		goto loop;
	}

	if (d == 0)
	{
		buff[n++] = '0';
		goto done;
	}

loop:
	rem = d % 10;
	d /= 10;

	if (d || rem)
	{
		buff[n++] = (int)('0') + rem;
		goto loop;
	}

done:
	ret += n; /* Accounts for minus */
	while(n--)
		tty_putc((int) buff[n]);

	return (ret);
}

static int kprint_hex (uint32_t d)
{
	int rem = 0, n = 0, ret = 0;
	char buff[10];

	for (; n < 8; n++)
	{
		rem = d % 16;
		d /= 16;

		if (rem < 10)
			buff[n] = (int)('0') + rem;
		else
			buff[n] = (int)('A') + (rem - 10);
	}

	buff[n++] = 'x';
	buff[n++] = '0'; 

	ret += n;
	while(n--)
		tty_putc((int) buff[n]);

	return (ret);
}

/* ============================ Public functions ============================ */

void kputc (int c)
{
	tty_putc(c);
}

int kprintf (const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int written = 0;

	while (*fmt != '\0')
	{
		/* Normal character */
		if (*fmt != '%')
		{
			int chnum = 0;

			/* Get longest sequence of normal characters */
			while (*fmt && *fmt != '%') { chnum++; tty_putc(*(fmt++)); }
			
			written += chnum;
		}
		/* Format specifier */
		else
		{
			/* Retrieve specifier */
			switch(*(++fmt))
			{
			case 'd': /* Integer */
			{
				int d = va_arg(args, int);
				written += kprint_int(d);
				break;
			}
			case 'h': /* Hex */
			{
				uint32_t d = va_arg(args, uint32_t);
				written += kprint_hex(d);
				break;
			}
			case 's': /* String */
			{
				const char *s = va_arg(args, const char *);
				written += tty_putstr(s);
				break;
			}
			case 'c': /* Character */
			{
				char c = (char) va_arg(args, int);
				tty_putc(c);
				written++;
				break;
			}
			case '%': /* Escape */
			{
				tty_putc('%');
				written++;
				break;
			}
			default: /* WRONG! */
				break;
			}

			/* Increment pointer */
			fmt++;
		}
	}

	va_end(args);

	return written;
}

void kpanic (const char *s, struct cpu_state *cpu, const char *fn, int line)
{
    __asm__ __volatile__ ("cli");

	tty_set_color(WHITE, RED);
	tty_cls();

    kprintf("%s at %s:%d", s, fn, line);

    if (cpu)
    {
    	kprintf("\n");
    	kprintf("Interrupt code: %h\n", cpu->int_no);
    	kprintf("    Error code: %h\n", cpu->err_no);
    	kprintf("\n");
    	kprintf("EAX: %h EBX: %h ECX: %h\n", cpu->eax, cpu->ebx, cpu->ecx);
    	kprintf("EDX: %h ESI: %h EDI: %h\n", cpu->edx, cpu->esi, cpu->edi);
    	kprintf("EIP: %h ESP: %h EBP: %h\n", cpu->eip, cpu->esp, cpu->ebp);
    	kprintf("\n");
    	kprintf(" CS: %h  DS: %h  ES: %h\n", cpu->cs,  cpu->ds,  cpu->es);
    	kprintf(" FS: %h  GS: %h  SS: %h\n", cpu->fs,  cpu->gs,  cpu->ss);
    	kprintf("\n");
    	kprintf("EFLAGS: %h\n", cpu->eflags);
    }
    
    __asm__ __volatile__ ("hlt");
}
