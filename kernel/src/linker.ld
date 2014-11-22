ENTRY(_start)
SECTIONS
{
  . = 1M;

  kstart = . ; _kstart = . ; __kstart = . ;

  .text BLOCK(4K) : 
  {
    *(.multiboot)
    *(.text)
  }

  .rodata BLOCK(4K) : 
  {
    *(.rodata)
  }

  .data BLOCK(4K) : 
  {
    *(.data)
  }

  .bss BLOCK(4K) : 
  {
    *(COMMON)
    *(.bss)
    *(.boostrap_stack)
  }

  kend = . ; _kend = . ; __kend = . ;
}
