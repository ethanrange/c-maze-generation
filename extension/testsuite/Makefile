CC      =   gcc
CFLAGS  =   -Wall
BUILD	=	testmaze

all:	make_src $(BUILD)

make_src:
	cd ../src; make;

clean:
	rm -f $(BUILD) $(OBJDIR)/*.o *.a core

test:	$(BUILD)
	summarisetests ./testmaze

testmaze:	testmaze.o testutils.o ../obj/utils.o
testmaze.o: testutils.h 
testutils.o:	testutils.h
