CC= gcc

CFLAGS= -g -Wall -std=c99 -I$(HOMEBREW_PATH)/include -I.
LDFLAGS= -L$(HOMEBREW_PATH)/lib -limago -lm


ALL_FILES= test-strelm test-mmip-1 test-mmip-2

OBJECTS= mmip-1-test.o mmip.o fft.o channel.o 

default: $(ALL_FILES)


test-strelm: test-strelm.o strelm.o
	$(CC) test-strelm.o strelm.o $(LDFLAGS) -o $@

test-mmip-1: test-mmip-1.o mmip.o strelm.o
	$(CC) test-mmip-1.o mmip.o strelm.o $(LDFLAGS) -o $@

test-mmip-2: test-mmip-2.o mmip.o strelm.o 
	$(CC) test-mmip-2.o mmip.o strelm.o $(LDFLAGS) -o $@

strelm.o: strelm.c strelm.h
mmip.o: mmip.c mmip.h strelm.h

test-strelm.o: test-strelm.c strelm.h
test-mmip-1.o: test-mmip-1.c mmip.h
test-mmip-2.o: test-mmip-2.c mmip.h


cleanall : clean
	rm -f $(ALL_FILES)
clean :  
	rm -f *.o





