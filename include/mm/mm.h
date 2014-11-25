/* 
 * File:   mm.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_MM_H
#define __KERNEL_MM_H

#include <stdint.h>

/* ========== Physical memory management ========== */

void *mm_allocate_frame (void);
void  mm_release_frame  (void *addr);

/* ========== Virtual memory management ========== */

void mm_paging_init (void);

#endif /* __KERNEL_MM_H */
