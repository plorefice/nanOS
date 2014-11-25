/* 
 * File:   serial_set_config.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>

#include "internals.h"
#include <drivers/serial.h>
#include <kernel/io.h>


/**
 * @brief Set the configuration of the specified port
 * @details Set the configuration of the specified port
 * 
 * @param port COMx, x = [1 .. 4]
 * @param config Structure containing configuration informations for the port
 */ 
void serial_set_config (uint8_t port, const struct serial_config *config)
{
	serial_set_baud_rate   (port, config->baud_rate);
	serial_set_break_bit   (port, config->break_bit);
	serial_set_parity_bit  (port, config->parity_bit);
	serial_set_stop_bit    (port, config->stop_bit);
	serial_set_word_length (port, config->word_length);
}
