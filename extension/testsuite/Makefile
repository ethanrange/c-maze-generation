CC      =   gcc 
CFLAGS  =   -Wall
BUILD	=	testmaze

all: 
	$(BUILD)

clean:
	rm -f $(BUILD) *.o core

test: $(BUILD)
	summarisetests ./testmaze

testmaze:    testmaze.o testutils.o
testmaze.o:  testmaze.c testutils.h
testutils.o: testutils.c testutils.h
