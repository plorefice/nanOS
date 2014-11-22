/* 
 * File:   paging.c
 * Author: Pietro Lorefice
 */

#include <stddef.h>
#include <stdint.h>

#include <kernel/paging.h>
#include <kernel/heap.h>
#include <kernel/mem.h>
#include <kernel/irq.h>
#include <kernel/io.h>

/* ============================ Private constants =========================== */

#define BITMAP_SIZE   (sizeof(uint32_t) * 8)
#define BITMAP_IDX(a) (a / BITMAP_SIZE)
#define BITMAP_OFF(a) (a % BITMAP_SIZE)

extern uintptr_t placement_addr;

/* ============================ Private variables =========================== */

struct page_directory *kernel_pd;
struct page_directory *current_pd;

static uint32_t *p_frames_bm;
static uint32_t  nframes;

/* =========================== External functions =========================== */

/* ============================ Private functions =========================== */

static void set_frame (uintptr_t addr)
{
    uintptr_t fa = addr >> 12;
    size_t idx = (size_t) BITMAP_IDX(fa);
    size_t off = (size_t) BITMAP_OFF(fa);
    p_frames_bm[idx] |= (0x1 << off);
}

static void clear_frame (uintptr_t addr)
{
    uintptr_t fa = addr >> 12;
    size_t idx = (size_t) BITMAP_IDX(fa);
    size_t off = (size_t) BITMAP_OFF(fa);
    p_frames_bm[idx] &= ~(0x1 << off);
}

static uint32_t test_frame (uintptr_t addr)
{
    uintptr_t fa = addr >> 12;
    size_t idx = (size_t) BITMAP_IDX(fa);
    size_t off = (size_t) BITMAP_OFF(fa);
    return (uint32_t)(p_frames_bm[idx] & (0x1 << off));
}

static size_t first_frame (void)
{
    size_t idx = 0, off = 0;
    
    for (idx = 0; idx < BITMAP_IDX(nframes); idx++)
        if (p_frames_bm[idx] != 0xFFFFFFFF)
            for (off = 0; off < BITMAP_SIZE; off++)
                if ((p_frames_bm[idx] & (0x1 << off)) == 0)
                    return (BITMAP_SIZE * idx + off);
    
    return (size_t)-1;
}

static void allocate_frame (struct page_entry *pg, uint8_t us, uint8_t rw)
{
    size_t frame_idx;

    if (pg->P != 0)
        return;
    else
    {
        frame_idx = first_frame();
        if (frame_idx == (size_t)-1)
            PANIC("No free memory!", 0);

        pg->ADDR = (uint32_t)(frame_idx);
        pg->P    = 1;
        pg->RW   = rw;
        pg->US   = us;
        
        set_frame(pg->ADDR * (0x1000));
    }
}

static void deallocate_frame (struct page_entry *pg)
{
    if (pg->P == 0)
        return;
    else
    {
        pg->P = 0;

        clear_frame(pg->ADDR);
    }
}

static void pagefault_handler (struct cpu_state *cpu)
{
    PANIC("PAGE FAULT", cpu);
}

/* ============================ Public functions ============================ */

void paging_init (void)
{
    uintptr_t pa;
    uint32_t cr0;

    /* 16MB memory */
    uintptr_t mem_end_addr = (0x1000000);
    
    nframes     = mem_end_addr / (0x1000);
    p_frames_bm = (uint32_t *) kmalloc((BITMAP_IDX(nframes) * sizeof(uint32_t)) + 1);
    kmemset(p_frames_bm, 0, (BITMAP_IDX(nframes) * sizeof(uint32_t)) + 1);

    kernel_pd = (struct page_directory *) kmalloc_a(sizeof(struct page_directory));
    kmemset(kernel_pd, 0, sizeof(struct page_directory));
    current_pd = kernel_pd;

    pa = 0;
    while (pa < placement_addr)
    {
        /* Can't use get_page_entry since paging hasn't been enabled yet */
        struct page_entry *pde = &(kernel_pd->pt[pa >> 22]);
        struct page_table *pt;
        struct page_entry *pg;

        if (pde->P == 0)
        {
            struct page_table *pt = (struct page_table *) kmalloc_a(sizeof(struct page_table));
            kmemset(pt, 0, sizeof(struct page_table));

            pde->P    = 1;
            pde->US   = 1;
            pde->RW   = 1;
            pde->ADDR = (uint32_t)((uintptr_t)(pt) >> 12);
        }
        else
        {
            pt = (struct page_table *) (pde->ADDR << 12);
        }

        pg = &(pt->p[(pa >> 12) & 0x003FF]);

        allocate_frame(pg, 0, 0);
        pa += 0x1000;
    }

    irq_install_handler(14, pagefault_handler);

    __asm__ __volatile__ ("mov %0, %%cr3" :: "r"(kernel_pd));
    __asm__ __volatile__ ("mov %%cr0, %0" : "=r"(cr0)); 
    cr0 |= 0x80000000;
    __asm__ __volatile__ ("mov %0, %%cr0" :: "r"(cr0));
}

void switch_page_directory (struct page_directory *pd)
{
}

struct page_entry* get_page_entry (void *addr)
{
    struct page_entry *pe = 0;

    return (pe);
}
