/* 
 * File:   serial_write.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>


/**
 * @brief Write up to count bytes from buffer to the specified port
 * @details Write up to count bytes from buffer to the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param buffer Pointer to a buffer containing data to send
 * @param count Number of bytes to send
 * 
 * @return 0 if successful, -1 otherwise
 */
int serial_write (uint8_t port, const void *buffer, size_t count)
{
	unsigned char *str = (unsigned char *) buffer;

	if (buffer == 0)
		return (-1);

	while (count--)
		serial_putchar(port, *(str++));

	return (0);
}
