/* 
 * File:   serial_set_baud_rate.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>

/**
 * @brief Set the baud rate of the specified port
 * @details Set the baud rate of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param baud_rate Baud rate (bit/s)
 */
void serial_set_baud_rate (uint8_t port, uint32_t baud_rate)
{
	uint16_t divisor = (uint16_t)(115200 / baud_rate);
	uint16_t base    = serial_base_addr[port]; 
	uint8_t  lcr;

	/* Read Line Control Register */
	lcr = inportb(SERIAL_LCR(base));

	/* Set DLAB bit */
	lcr |= SERIAL_DLAB;
	outportb(SERIAL_LCR(base), lcr);

	/* Set Divisor Latch Low */
	outportb(SERIAL_DLL(base), (uint8_t)(divisor & 0x00FF));

	/* Set Divisor Latch High */
	outportb(SERIAL_DLH(base), (uint8_t)(divisor >> 8));

	/* Restore Line Control Register */
	lcr &= 0x7F;
	outportb(SERIAL_LCR(base), lcr);
}
