/* 
 * File:   serial_set_parity.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Set the parity bit of the specified port
 * @details Set the parity bit of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param parity_bit SERIAL_PARITY_x
 */
void serial_set_parity_bit (uint8_t port, uint8_t parity_bit)
{
	uint16_t base = serial_base_addr[port];
	uint8_t  lcr;

	/* Read Line Control Register */
	lcr = inportb(SERIAL_LCR(base));

	/* Set parity bit */
	lcr |= parity_bit;
	outportb(SERIAL_LCR(base), lcr);
}
