/* 
 * File:   mm_init.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>
#include "internals.h"

uint32_t mm_pmem_bitmap[PMEM_NUMFRAMES]; // 512-byte bitmap
