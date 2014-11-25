/* 
 * File:   serial_set_word_length.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Set the word length of the specified port
 * @details Set the word length of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param word_length SERIAL_WLEN_x
 */
void serial_set_word_length (uint8_t port, uint8_t word_length)
{
	uint16_t base = serial_base_addr[port];
	uint8_t  lcr;

	/* Read Line Control Register */
	lcr = inportb(SERIAL_LCR(base));

	/* Set word length */
	lcr |= word_length;
	outportb(SERIAL_LCR(base), lcr);
}
