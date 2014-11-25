/* 
 * File:   serial_set_stop_bits.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Set the number of stop bits of the specified port
 * @details Set the number of stop bits of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param stop_bit SERIAL_STOP_x
 */
void serial_set_stop_bit (uint8_t port, uint8_t stop_bit)
{
	uint16_t base = serial_base_addr[port];
	uint8_t  lcr;

	/* Read Line Control Register */
	lcr = inportb(SERIAL_LCR(base));

	/* Set stop bits */
	lcr |= stop_bit;
	outportb(SERIAL_LCR(base), lcr);
}
