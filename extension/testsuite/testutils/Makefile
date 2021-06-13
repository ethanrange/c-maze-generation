# destination: install into TOOLDIR (env var, eg ~/c-tools)
TOOLDIR =       ./
DEST    =       $(TOOLDIR)
BINDIR  =       $(DEST)/bin
INCDIR  =       $(DEST)/include
LIBDIR  =       $(DEST)/lib/$(ARCH)
CC	=	gcc
CFLAGS	=	-Wall
LDLIBS	=	-ltestlib
LIB     =       libtestlib.a
LIBOBJS	=	testutils.o
BUILD	=	$(LIB)

all:	$(BUILD)

clean:
	/bin/rm -f $(BUILD) *.o core

$(LIB): $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

install:	$(BUILD)
	install -m 755 summarisetests $(BINDIR)
	install -m 644 $(LIB) $(LIBDIR)
	install -m 644 testutils.h $(INCDIR)
