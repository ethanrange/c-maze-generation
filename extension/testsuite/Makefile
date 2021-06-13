TOOLDIR =       ./testutils
INSTDIR =       $(TOOLDIR)
INCDIR  =       $(INSTDIR)/include
LIBDIR  =       $(INSTDIR)/lib/$(ARCH)
CC      =       gcc
CFLAGS  =       -Wall -I$(INCDIR)
LDLIBS  =       -L$(LIBDIR) -ltestlib
#LIBOBJS	=	.o
BUILD	=	testmaze $(LIB)

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

test:	$(BUILD)
	cd testutils;make clean && make; cd ..; summarisetests ./testmaze

testmaze:	testmaze.o 
testmaze.o:	testmaze.c