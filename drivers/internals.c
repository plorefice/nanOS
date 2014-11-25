/* 
 * File:   internals.c
 * Author: Pietro Lorefice
 */

 #include <stdint.h>

 #include "internals.h"

const uint16_t serial_base_addr[] =
	{
		0x0,                /* UNDEFINED! */
		SERIAL_COM1_BASE,   /* COM1 */
		SERIAL_COM2_BASE,   /* COM2 */
		SERIAL_COM3_BASE,   /* COM3 */
		SERIAL_COM4_BASE    /* COM4 */
	};
