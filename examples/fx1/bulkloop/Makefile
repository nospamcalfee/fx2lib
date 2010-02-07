BASEDIR = ../../..
LIBS = 
BASENAME = bulkloop
SOURCES = bulkloop.c bulkloopint.c descriptors.c fx1setup.c
A51_SOURCES=$(BASEDIR)/lib/fx1jt.a51
SDCCFLAGS += --code-loc 0x00 --code-size 0x1a00
SDCCFLAGS += -Wl"-b INT2JT = 0x1a00"
include $(BASEDIR)/lib/fx1.mk



