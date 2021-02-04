CFLAGS = -g -Wall -Wstrict-prototypes
PROGS = display_image
LDFLAGS = -lX11
CC = gcc

all: $(PROGS)

display_image: display_image.o load-image.o convert-to-16bit-RGB.o $(LDFLAGS)

clean: 
	rm -f $(PROGS) *.o core*
