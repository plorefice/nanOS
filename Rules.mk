# Standard stuff
all:                   targets

# Inlcude sub-modules
dir :=                 kernel
include                $(dir)/Rules.mk
dir :=                 drivers
include                $(dir)/Rules.mk

# General rules for compilation and assembly
%.o:                   %.c
	                   @$(COMP)

%.o:                   %.s
	                   @$(ASMB)

# Additional rules
.PHONY:                targets
targets:               $(TGT_BIN) $(TGT_LIB)
         
.PHONY:                clean
clean:         
	                   @$(RM) $(CLEAN)
	                   @$(RM) $(LIBS)/*
	                   @$(RM) $(EXES)/*
	                   @$(RM) iso/boot/nanOS.elf
	                   @$(RM) iso/nanOS.iso

.PHONY:                boot
boot:                  iso/nanOS.iso
	                   @bochs -f bochsrc.txt -q

iso/nanOS.iso:         all
	                   @cp bin/kernel iso/boot/nanOS.elf
	                   @mkisofs -R -quiet                     \
	                            -b boot/grub/stage2_eltorito  \
	                            -no-emul-boot                 \
	                            -boot-load-size 4             \
	                            -boot-info-table              \
	                            -o iso/nanOS.iso              \
	                            iso
         
         
.SECONDARY:            $(CLEAN)
