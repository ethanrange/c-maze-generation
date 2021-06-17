CC      =   gcc
CFLAGS  =   -Wall

OBJDIR 	= 	../obj
BINDIR  =   ../bin

BUILD	=	make_src $(BINDIR)/testmaze

_TESTMAZE   = testmaze.o testutils.o utils.o
TESTMAZE    = $(patsubst %,$(OBJDIR)/%,$(_TESTMAZE))

all:	$(BUILD)

make_src:
	cd ../src; make;

clean:
	rm -fv $(BUILD) $(OBJDIR)/*.o *.a core

test: $(BUILD)
	summarisetests $(BINDIR)/testmaze

$(BINDIR)/testmaze: $(TESTMAZE)	

# Compile binary executables to bin; create directory if it doesn't exist
$(BINDIR)/%:
		@mkdir -p $(@D)
		$(CC) $^ -o $@

$(OBJDIR)/testmaze.o: testmaze.c testutils.h
$(OBJDIR)/testutils.o: testutils.c testutils.h

# Compile object files to obj; create directory if it doesn't exist
$(OBJDIR)/%.o:
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@
