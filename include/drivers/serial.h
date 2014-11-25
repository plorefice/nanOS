/* 
 * File:   serial.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_DRIVERS_SERIAL_H
#define __KERNEL_DRIVERS_SERIAL_H 1

#include <stddef.h>
#include <stdint.h>

#define SERIAL_BREAK_DISABLED (0x40)
#define SERIAL_BREAK_ENABLED  (0x40)

#define SERIAL_PARITY_NONE    (0x00)
#define SERIAL_PARITY_ODD     (0x08)
#define SERIAL_PARITY_EVEN    (0x18)
#define SERIAL_PARITY_MARK    (0x28)
#define SERIAL_PARITY_SPACE   (0x38)

#define SERIAL_STOP_1         (0x00)
#define SERIAL_STOP_1_5       (0x04)
#define SERIAL_STOP_2         (0x04)

#define SERIAL_WLEN_5         (0x00)
#define SERIAL_WLEN_6         (0x01)
#define SERIAL_WLEN_7         (0x02)
#define SERIAL_WLEN_8         (0x03)

struct serial_config
{
	uint32_t baud_rate;
	uint8_t  break_bit;
	uint8_t  parity_bit;
	uint8_t  stop_bit;
	uint8_t  word_length;
};


void serial_set_config      (uint8_t port, const struct serial_config *config);
void serial_set_fifo_config (uint8_t port);

void serial_set_baud_rate   (uint8_t port, uint32_t baud_rate);
void serial_set_break_bit   (uint8_t port, uint8_t  break_bit);
void serial_set_parity_bit  (uint8_t port, uint8_t  parity_bit);
void serial_set_stop_bit    (uint8_t port, uint8_t  stop_bit);
void serial_set_word_length (uint8_t port, uint8_t  word_length);

int  serial_putchar         (uint8_t port, unsigned char c);
int  serial_write           (uint8_t port, const void *buffer, size_t count);


#endif /* __KERNEL_DRIVERS_SERIAL_H */
