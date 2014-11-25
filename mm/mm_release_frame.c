/* 
 * File:   mm_release_frame.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>
#include "internals.h"

/**
 * @brief Relases a frame
 * @details This function releases a previously allocated frame in physical
 *          memory, using its physical address, and marks it as free.
 * 
 * @param addr [description]
 */
void mm_release_frame (void *addr)
{
	uintptr_t p = (uintptr_t) addr >> 12;

	size_t idx = p / BM_BITLEN;
	size_t off = p % BM_BITLEN;

	mm_clear_frame(idx, off);
}
