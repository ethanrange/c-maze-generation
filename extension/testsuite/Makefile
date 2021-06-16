RAYLIB_PATH = ../raylib/src

SRC_PATH = ../src/
CC      =       gcc
CFLAGS  =       -Wall -I$(RAYLIB_PATH) -I$(SRC_PATH)
LIB	    =	utils.a
LIBOBJS	=	$(SRC_PATH)utils.o
BUILD	=	testmaze $(LIB)

all:	$(BUILD)

clean:
	rm -f $(BUILD) $(OBJDIR)/*.o core

$(LIB):		$(LIBOBJS)
	ar rc $(LIB) $(LIBOBJS)
	ranlib $(LIB)

test:	$(BUILD)
	summarisetests ./testmaze

testmaze:	testmaze.o testutils.o utils.a
testmaze.o: testutils.h 
testutils.o:	testutils.h
utils.o:	utils.c constants.h utils.h 
