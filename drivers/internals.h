/* 
 * File:   internals.h
 * Author: Pietro Lorefice
 */

#ifndef __INTERNALS_H
#define __INTERNALS_H 1

#include <stdint.h>

#define SERIAL_COM1_BASE  (0x3F8)
#define SERIAL_COM2_BASE  (0x2F8)
#define SERIAL_COM3_BASE  (0x3E8)
#define SERIAL_COM4_BASE  (0x2E8)
 
#define SERIAL_THR(base)  (base)
#define SERIAL_RBR(base)  (base)
#define SERIAL_DLL(base)  (base)
#define SERIAL_IER(base)  (base + 1)
#define SERIAL_DLH(base)  (base + 1)
#define SERIAL_IIR(base)  (base + 2)
#define SERIAL_FCR(base)  (base + 2)
#define SERIAL_LCR(base)  (base + 3)
#define SERIAL_MCR(base)  (base + 4)
#define SERIAL_LSR(base)  (base + 5)
#define SERIAL_MSR(base)  (base + 6)
 
#define SERIAL_DLAB       (0x80)


extern const uint16_t serial_base_addr[];


#endif /* __INTERNALS_H */
