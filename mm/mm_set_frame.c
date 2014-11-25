/* 
 * File:   mm_set_frame.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include "internals.h"
 
/**
 * @brief Mark a frame as used
 * @details This function marks the frame identified by the pair (idx,off) as
 *          used, and thus not eligible to be allocated until freed.
 * 
 * @param idx Index of the entry in the bitmap
 * @param off Offset of the frame in the bitmap entry
 */
void mm_set_frame (size_t idx, size_t off)
{
	mm_pmem_bitmap[idx] |= (1U << off);
}
