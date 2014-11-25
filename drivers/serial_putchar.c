/* 
 * File:   serial_putchar.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Writes the byte c to the specified port
 * @details Writes the byte c to the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param c Byte to send
 * 
 * @return 0 if successful, -1 otherwise
 */
int serial_putchar (uint8_t port, unsigned char c)
{
	uint16_t base = serial_base_addr[port];

	/* Wait until the transmitter is ready to send */
	while ((inportb(SERIAL_LSR(base)) & 0x20) == 0) ;

	/* Send byte */
	outportb(SERIAL_THR(base), c);

	return (0);
}
