# Push current directory onto the stack
sp                      := $(sp).x
dirstack_$(sp)          := $(d)
d                       := $(dir)

# Target-specific local variables
TGTN_$(d)               := kernel                      # Target name
TGTS_$(d)	            := $(d)/$(TGTN_$(d))           # Target path
DEPS_$(d)	            := $(TGTS_$(d):%=%.d)          # Target dependencies

OBJS_$(d)               := $(patsubst %.c,%.o,$(wildcard $(d)/*.c)) \
                           $(patsubst %.s,%.o,$(wildcard $(d)/*.s))
DEPS_$(d)               := $(DEPS_$(d)) $(OBJS_$(d):%.o=%.d)

LIBS_$(d)               := libdrivers.a                # Library dependencies

# Update global variables 
TGT_BIN		            := $(TGT_BIN) $(TGTS_$(d))
CLEAN		            := $(CLEAN) $(TGTS_$(d)) $(DEPS_$(d)) $(OBJS_$(d))

# Target-specific rules
$(OBJS_$(d)):           CFLAGS_TGT := -ffreestanding -Wall -Wextra \
	                                  -Wno-packed-bitfield-compat

$(TGTS_$(d)):           LDFLAGS_TGT := -T$(d)/linker.ld -nostdlib -lgcc
$(TGTS_$(d)):           $(OBJS_$(d)) $(addprefix $(LIBS)/,$(LIBS_$(d)))
					    @$(LINK)

# Include dipendencies
-include	$(DEPS_$(d))

# Pop previously saved directory
d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
