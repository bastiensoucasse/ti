CFLAGS := -std=c99 -g -Wall -I/opt/homebrew/include -I.
LDFLAGS := -limago -lpng -ljpeg -lfftw3 -lm

.PHONY: all
all: test-glfip-1

test-glfip-1: test-glfip-1.o fft.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

fft.o: src/fft.c
	$(CC) $(CFLAGS) -o $@ -c $^

test-glfip-1.o: src/test-glfip-1.c
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	$(RM) *.o *~
