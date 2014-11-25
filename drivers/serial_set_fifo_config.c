/* 
 * File:   serial_set_fifo_config.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Configure and enable FIFO of the specified port
 * @details Configure and enable FIFO of the specified port
 * 
 * @param port COMx, x = [1 ..4]
 */
void serial_set_fifo_config (uint8_t port)
{
	uint16_t base = serial_base_addr[port];
	uint8_t  fcr;

	/* Set FIFO control register */
	fcr = 0xC7;
	outportb(SERIAL_FCR(base), fcr);
}
