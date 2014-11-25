# CFLAGS for module
CFLAGS_kernel_mm  := -ffreestanding -fbuiltin -Wall -Wextra -Wno-packed-bitfield-compat
ASFLAGS_kernel_mm := 
LDFLAGS_kernel_mm := 

# Archive / Lib to build in module
kernel_mm_ARCHIVE := kernel/libmm.a

# Sources for the archive / lib (without headers)
libmm.a_SOURCES := $(notdir $(wildcard kernel/mm/src/*.c))

DEPENDENCIES := $(DEPENDENCIES) $(patsubst %,kernel/mm/obj/%.d,$(basename $(libmm.a_SOURCES)))

kernel/mm/obj/%.o: kernel/mm/src/%.c
	@$(CC) $(CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra -Wno-packed-bitfield-compat -I. -c $< -o $@

lib/kernel/libmm.a: $(patsubst %,kernel/mm/obj/%.o,$(basename $(libmm.a_SOURCES)))
	@mkdir -p lib/kernel
	@$(AR) $(ARFLAGS) $@ $?
