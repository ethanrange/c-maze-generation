gcc main.c -g -std=c99 -c -I../raylib/src -o main.o
gcc main.o -s -Wall -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -DPLATFORM_DESKTOP -I/usr/local/include -L. -L/usr/local/lib -L../raylib
