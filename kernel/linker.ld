ENTRY(_bootstrap)
KERNEL_BOOT_VMA   = 0x00100000;
KERNEL_VMA_OFFSET = 0xC0000000;
SECTIONS
{
  . = KERNEL_BOOT_VMA;

  _boot_start = . ; __boot_start = . ;

  .boot ALIGN(4K) :
  {
    *(.boot)
    . = ALIGN(4K);
  }

  _boot_end = . ; __boot_end = . ;

  . += KERNEL_VMA_OFFSET;

  _kernel_start = . ; __kernel_start = . ;

  .text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VMA_OFFSET)
  {
    *(.text)
    *(.rodata)
  }

  .data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VMA_OFFSET)
  {
    *(.data)
  }

  .bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VMA_OFFSET)
  {
    _sbss = . ;
    *(COMMON)
    *(.bss)
    . = ALIGN(4K);
    _ebss = . ;
  }

  _kernel_end = . ; __kernel_end = . ;

}
