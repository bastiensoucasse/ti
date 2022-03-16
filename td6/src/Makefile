CC= gcc
CFLAGS= -g -Wall -std=c99 
LDFLAGS= -L$(ROOT)/lib -L$(DEVELROOT)/lib -limago -lm

ALL_FILES= test-1 test-2 test-3 test-4 test-5 test-6 
OBJECTS_1= bbox.o channel.o convol1d.o img.o 
OBJECTS_2= $(OBJECTS_1) pderiv.o deriche.o
OBJECTS_3= $(OBJECTS_2)
OBJECTS_4= $(OBJECTS_3) gradient.o
OBJECTS_5= $(OBJECTS_4)
OBJECTS_6= threshold.o histogram.o stif.o bbox.o hysteresis.o img.o


default: test-1
all: $(ALL_FILES)

test-1: $(OBJECTS_1) test-1.o
	$(CC) test-1.o $(OBJECTS_1) $(LDFLAGS) -o $@

test-2: $(OBJECTS_2) test-2.o
	$(CC) test-2.o $(OBJECTS_2) $(LDFLAGS) -o $@

test-3: $(OBJECTS_3) test-3.o
	$(CC) test-3.o $(OBJECTS_3) $(LDFLAGS) -o $@

test-4: $(OBJECTS_4) test-4.o
	$(CC) test-4.o $(OBJECTS_4) $(LDFLAGS) -o $@

test-5: $(OBJECTS_5) test-5.o
	$(CC) test-5.o $(OBJECTS_5) $(LDFLAGS) -o $@

test-6: $(OBJECTS_6) test-6.o
	$(CC) test-6.o $(OBJECTS_6) $(LDFLAGS) -o $@

test-1.o: test-1.c channel.h convol1d.h img.h
test-2.o: test-1.c channel.h convol1d.h img.h pderiv.h
test-3.o: test-3.c channel.h convol1d.h pderiv.h img.h
test-4.o: test-4.c channel.h convol1d.h pderiv.h img.h gradient.h
test-5.o: test-5.c channel.h convol1d.h pderiv.h img.h gradient.h
test-6.o: test-6.c threshold.h hysteresis.h img.h

channel.o: channel.c channel.h
convol1d.o: convol1d.c convol1d.h
img.o: img.c img.h
pderiv.o: pderiv.c convol1d.h deriche.h pderiv.h
deriche.o: deriche.c deriche.h
gradient.o: gradient.c gradient.h

threshold.o: threshold.c histogram.h stif.h threshold.h
histogram.o: histogram.c bbox.h histogram.h
stif.o: stif.c histogram.h stif.h
bbox.o: bbox.c bbox.h
hysteresis.o: hysteresis.c threshold.h hysteresis.h




#----------------------

cleanall : clean
	rm -f $(ALL_FILES)
clean :  
	rm -f $(OBJECTS_4)  $(OBJECTS_6) test-?.o

#----------------------


