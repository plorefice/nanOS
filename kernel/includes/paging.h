/* 
 * File:   paging.h
 * Author: Pietro Lorefice
 */

#ifndef __KERNEL_PAGING_H
#define __KERNEL_PAGING_H

#include <stdint.h>

#include <kernel/descriptors.h>

/* =========================== Exported constants =========================== */

/* ============================= Exported types ============================= */

/* Represents an entry in the Page-Table or Page-Directory 
 *
 *  31                          12   7 6 5   4   3  2  1 0
 *  +---------------------------------------------------+
 *  |            ADDR           |IGN|D|A|PCD|PWT|US|RW|P|
 *  +---------------------------------------------------+
 */
struct page_entry
{
    uint8_t  P    :  1; /* The page referred by this entry exists in memory */
    uint8_t  RW   :  1; /* 1: Read/write ; 0: Read only */
    uint8_t  US   :  1; /* User-mode access allowed */
    uint8_t  PWT  :  1; /* Write-through */
    uint8_t  PCD  :  1; /* Cache disable */
    uint8_t  A    :  1; /* The entry has been accessed for translation */
    uint8_t  D    :  1; /* The page referred by this entry has been modified */
    uint8_t  IGN  :  5; /* RESERVED */
    uint32_t ADDR : 20; /* Upper 20-bit of the page's physical address */
} __attribute__((packed));

/* Represents a Page-Table*/
struct page_table
{
    struct page_entry p[1024]; /* 1024 page entries (4K total size) */
};

/* Represents a Page-Directory*/
struct page_directory
{
    struct page_entry pt[1024]; /* 1024 page-table entries (4K total size) */
};

/* =========================== Exported variables =========================== */

/* =========================== Exported functions =========================== */

             void  paging_init           (void);
             void  switch_page_directory (struct page_directory *pd);
struct page_entry *get_page_entry        (void *addr);

#endif /* __KERNEL_PAGING_H */
