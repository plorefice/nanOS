# Push current directory onto the stack
sp                      := $(sp).x
dirstack_$(sp)          := $(d)
d                       := $(dir)

# Target-specific local variables
TGTN_$(d)               := libdrivers.a              # Target name
TGTS_$(d)	            := $(d)/$(TGTN_$(d))         # Target path
DEPS_$(d)	            := $(TGTS_$(d):%=%.d)        # Target dependencies

OBJS_$(d)               := $(patsubst %.c,%.o,$(wildcard $(d)/*.c))
DEPS_$(d)               := $(DEPS_$(d)) $(OBJS_$(d):%.o=%.d)

# Update global variables 
TGT_LIB		            := $(TGT_LIB) $(TGTS_$(d))
CLEAN		            := $(CLEAN) $(TGTS_$(d)) $(DEPS_$(d)) $(OBJS_$(d))

# Target-specific rules
$(OBJS_$(d)):           CFLAGS_TGT := -ffreestanding -Wall -Wextra    \
	                                  -Wno-packed-bitfield-compat -I.

$(LIBS)/$(TGTN_$(d)):   $(TGTS_$(d))
$(TGTS_$(d)):           $(OBJS_$(d))
					    @$(ARCH)

# Include dipendencies
-include	$(DEPS_$(d))

# Pop previously saved directory
d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
