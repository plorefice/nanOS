/* 
 * File:   mm_clear_frame.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include "internals.h"

/**
 * @brief Mark a frame as unused
 * @details This function marks the frame identified by the pair (idx,off) as
 *          unused, and thus eligible for allocation.
 * 
 * @param idx Index of the entry in the bitmap
 * @param off Offset of the frame in the bitmap entry
 */
void mm_clear_frame (size_t idx, size_t off)
{
	mm_pmem_bitmap[idx] &= ~(1U << off);
}
