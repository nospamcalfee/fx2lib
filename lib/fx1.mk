# common make targets for compiling fx1 firmware
#
# In your Makefile, define:
# SOURCES: list of c files to compile
# A51_SOURCES: list of any a51 files.
# BASENAME: name of your firmware file, i.e., myfirmware, but not myfirmware.c
# BASEDIR: top directory of fx2lib.  Contains lib and include dirs
#
# Provided targets:
#
# default target: creates $(BASENAME).ihx
# bix: creates $(BASENAME).bix
# iic: creates $(BASENAME).iic
# load: uses fx2load to load firmware.bix onto the development board
#  (You can customize VID/PID if you need to load the firmware onto a device that has different vendor and product id
#  The default is  0x04b4, 0x8613
# clean: delete all the temp files.
#
#
#

ifndef VID
VID=0x04b4
endif
ifndef PID
PID=0x8613
endif

RELS=$(SOURCES:.c=.rel) $(A51_SOURCES:.a51=.rel)
# these are pretty good settings for most firmwares.  
# Have to be careful with memory locations for 
# firmwares that require more xram etc.
CC = sdcc -mmcs51 $(SDCCFLAGS)

.PHONY: ihx iic bix load clean


ihx: $(BASENAME).ihx
bix: $(BASENAME).bix
iic: $(BASENAME).iic

# can't use default target %.rel because there is no way
# to differentiate the dependency.  (Is it %.rel: %.c or %.a51)
$(BASENAME).ihx: $(SOURCES) $(A51_SOURCES)
	for a in $(A51_SOURCES); do \
	 asx8051 -logs $$a; done
	for s in $(SOURCES); do \
	 $(CC) -c -I $(BASEDIR)/include $$s; done
	$(CC) -o $(BASENAME).ihx $(RELS) $(LIB) -L $(BASEDIR)/lib


$(BASENAME).bix: $(BASENAME).ihx
	objcopy -I ihex -O binary $< $@
$(BASENAME).iic: $(BASENAME).ihx
	$(BASEDIR)/utils/ihx2iic.py -v $(VID) -p $(PID) $< $@

load: $(BASENAME).bix
	fx2load -v $(VID) -p $(PID) $(BASENAME).bix
	
clean:
	rm -f *.{asm,ihx,lnk,lst,map,mem,rel,rst,sym,adb,cdb,bix}
