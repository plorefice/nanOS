# Environment variables
PATH := $(HOME)/opt/cross/bin:$(PATH)
HOST := i686-elf

# Project directories
EXES := bin
LIBS := lib
INCS := include

# Global compilation flags
CFLAGS  := -MMD -O0 -g -I./$(INCS)
ASFLAGS := -f elf
LDFLAGS := -fno-use-linker-plugin -L./$(LIBS)
ARFLAGS := rcs

# Cross toolchain
AR := $(HOST)-ar
AS := nasm
CC := $(HOST)-gcc

# Common commands
CP := cp
RM := rm -f

#Compilation commands
ARCH = $(AR) $(ARFLAGS) $(ARFLAGS_TGT)    $@    $?  &&  $(CP) $@ $(LIBS)
ASMB = $(AS) $(ASFLAGS) $(ASFLAGS_TGT) -o $@    $<
COMP = $(CC) $(CFLAGS)  $(CFLAGS_TGT)  -o $@ -c $<
LINK = $(CC) $(LDFLAGS) $(LDFLAGS_TGT) -o $@    $^  &&  $(CP) $@ $(EXES)

# Standard rules
include Rules.mk
