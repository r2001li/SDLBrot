CC=gcc
CFLAGS=-lSDL2
DEPS = mandelbrot.h renderthread.h
OBJ = app.o mandelbrot.o renderthread.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mandelbrot: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
