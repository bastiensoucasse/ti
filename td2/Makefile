CC= gcc
CFLAGS= -g -Wall -std=c99 

OBJECTS= xyz.o colorimetric_data.o sed.o dispsed.o

default: dispsed

dispsed : $(OBJECTS)
	$(CC) -o dispsed $(OBJECTS) -lm


sed.o: sed.c sed.h 
xyz.o: xyz.c xyz.h
colorimetric_data.o: colorimetric_data.c colorimetric_data.h


clean :
	rm -f $(OBJECTS) 

cleanall: clean
	rm -f dispsed
