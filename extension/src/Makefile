.PHONY: all clean

UNAMEOS=$(shell uname)

ifeq ($(UNAMEOS),Linux)
	PLATFORM_OS=LINUX
endif
		
ifeq ($(UNAMEOS),Darwin)
	PLATFORM_OS=OSX
endif

PLATFORM = PLATFORM_DESKTOP

RAYLIB_PATH = ../raylib/
RAYLIB_INSTALL_PATH = ../raylib/
RAYLIB_H_INSTALL_PATH = ../raylib/

RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src

# Define default C compiler: gcc
# NOTE: define g++ compiler if using C++
CC = gcc

# Define default make program
MAKE = make

# Define compiler flags:
#  -O1                  defines optimization level
#  -g                   include debug information on compilation
#  -s                   strip unnecessary data from build
#  -Wall                turns on most, but not all, compiler warnings
#  -std=c99             defines C language mode (standard C from 1999 revision)
#  -std=gnu99           defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces  ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE    use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wno-unused-command-line-argument -Werror -pedantic -s -O

ifeq ($(PLATFORM_OS),LINUX)
		ifeq ($(RAYLIB_LIBTYPE),STATIC)
			CFLAGS += -D_DEFAULT_SOURCE
		endif
endif

# Define include paths for required headers
# NOTE: Some external/extras libraries could be required (stb, physac, easings...)
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I$(RAYLIB_PATH)/src/extras

ifeq ($(PLATFORM_OS),LINUX)
	INCLUDE_PATHS += -I$(RAYLIB_H_INSTALL_PATH)
endif

# Define library paths containing required libs.
LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src

ifeq ($(PLATFORM_OS),LINUX)
	# Reset everything.
	# Precedence: immediately local, installed version, raysan5 provided libs
	LDFLAGS = -L. -L$(RAYLIB_INSTALL_PATH) -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)
endif
# Define any libraries required on linking
# if you want to link libraries (libname.so or libname.a), use the -lname
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
	ifeq ($(PLATFORM_OS),LINUX)
		# Libraries for Debian GNU/Linux desktop compiling
		# NOTE: Required packages: libegl1-mesa-dev
		LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt

		# On X11 requires also below libraries
		LDLIBS += -lX11
		# NOTE: It seems additional libraries are not required any more, latest GLFW just dlopen them
		#LDLIBS += -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor

		# On Wayland windowing system, additional libraries requires
		ifeq ($(USE_WAYLAND_DISPLAY),TRUE)
			LDLIBS += -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
		endif
		# Explicit link to libc
		ifeq ($(RAYLIB_LIBTYPE),SHARED)
			LDLIBS += -lc
		endif
	endif
	ifeq ($(PLATFORM_OS),OSX)
		# Libraries for OSX 10.9 desktop compiling
		# NOTE: Required packages: libopenal-dev libegl1-mesa-dev
		LDLIBS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ../raylib/src/libraylib.a
	endif
endif

# Default target entry
all:	libraylib main

main:	main.o utils.o prims.o kruskals.o recursive_backtrack.o dijkstras.o visualiser.o

main.o:	main.c constants.h utils.h prims.h kruskals.h recursive_backtrack.h dijkstras.h visualiser.h
utils.o:	utils.c constants.h utils.h
prims.o:	prims.c constants.h utils.h prims.h
kruskals.o:	kruskals.c constants.h utils.h kruskals.h
recursive_backtrack.o:	recursive_backtrack.c constants.h utils.h recursive_backtrack.h
dijkstras.o:	dijkstras.c constants.h utils.h dijkstras.h
visualiser.o:	visualiser.c constants.h utils.h prims.h kruskals.h recursive_backtrack.h dijkstras.h visualiser.h

%.o:
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM) -c $< -o $@

# Makes libraylib.a to be used as a static library
libraylib:
ifeq ($(PLATFORM_OS),LINUX)
	cd ../raylib/src; make PLATFORM=PLATFORM_DESKTOP GRAPHICS=GRAPHICS_API_OPENGL_11
else
	cd ../raylib/src; make
endif

# Clean everything
clean:
ifeq ($(PLATFORM_OS),LINUX)
	find . -type f -executable -delete
	rm -fv *.o
endif

ifeq ($(PLATFORM_OS),OSX)
	find . -type f -perm +ugo+x -delete
	rm -f *.o
endif