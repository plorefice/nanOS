/* 
 * File:   mm_allocate_frame.c
 * Author: Pietro Lorefice
 */

#include <stdint.h>
#include "internals.h"

/**
 * @brief Allocates a free frame
 * @details This function finds the first available physical frame, marks it
 *			as occupied, and returns the physical address of the frame.
 *
 * @return Physical address of the frame
 */		
void *mm_allocate_frame (void)
{
	size_t idx, off;

	/* For each bitmap entry */
	for (idx = 0; idx < PMEM_NUMFRAMES; idx++)
		/* If there's a free frame in the entry */
		if (mm_pmem_bitmap[idx] != 0xFFFFFFFF)
			/* Look for said free frame */
			for (off = 0; off < BM_BITLEN; off++)
				/* And once it's found */
				if ((mm_pmem_bitmap[idx] & (1U << off)) == 0)
					/* stop */
					goto out;

out:
	mm_set_frame(idx, off);

	return (void *)((idx * BM_BITLEN + off) * FRAME_SIZE);
}
