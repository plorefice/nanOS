/* 
 * File:   internals.h
 * Author: Pietro Lorefice
 */

#ifndef __INTERNALS_H
#define __INTERNALS_H

#include <stdint.h>
#include <stddef.h>

#include <kernel/utils.h>

#define PMEM_SIZE   MiB(16)
#define FRAME_SIZE  KiB(4)
#define BM_BITLEN   32

#define PMEM_NUMFRAMES (PMEM_SIZE / FRAME_SIZE)

extern uint32_t mm_pmem_bitmap[];


void mm_set_frame   (size_t idx, size_t off);
void mm_clear_frame (size_t idx, size_t off);


#endif /* __INTERNALS_H */