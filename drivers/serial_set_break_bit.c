/* 
 * File:   serial_set_break_bit.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Set the break bit of the specified port
 * @details Set the break bit of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param break SERIAL_BREAK_x
 */
void serial_set_break_bit (uint8_t port, uint8_t break_bit)
{
	uint16_t base = serial_base_addr[port];
	uint8_t  lcr;

	/* Read Line Control Register */
	lcr = inportb(SERIAL_LCR(base));

	/* Set break bit */
	lcr |= break_bit;
	outportb(SERIAL_LCR(base), lcr);
}
