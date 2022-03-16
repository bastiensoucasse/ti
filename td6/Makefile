CC := clang
CFLAGS := -std=c17 -O3 -Wall -Iinclude -I$(HOMEBREW_PATH)/include
LDFLAGS := -L$(HOMEBREW_PATH)/lib -limago -ljpeg -lpng -lfftw3 -lm

BUILDDIR := build
SRCDIR := src

DATADIR := images

.PHONY: all
all: test-1 test-2 # test-3 # test-4 # test-5 # test-6

.PHONY: test-1 test-2 test-3 test-4 test-5 test-6
test-1: $(BUILDDIR)/test-1
$(BUILDDIR)/test-1: $(BUILDDIR)/test-1.o $(BUILDDIR)/channel.o $(BUILDDIR)/convol1d.o $(BUILDDIR)/img.o
test-2: $(BUILDDIR)/test-2
$(BUILDDIR)/test-2: $(BUILDDIR)/test-2.o $(BUILDDIR)/channel.o $(BUILDDIR)/convol1d.o $(BUILDDIR)/img.o $(BUILDDIR)/pderiv.o
test-3: $(BUILDDIR)/test-3
$(BUILDDIR)/test-3: $(BUILDDIR)/test-3.o $(BUILDDIR)/img.o
test-4: $(BUILDDIR)/test-4
$(BUILDDIR)/test-4: $(BUILDDIR)/test-4.o $(BUILDDIR)/img.o
test-5: $(BUILDDIR)/test-5
$(BUILDDIR)/test-5: $(BUILDDIR)/test-5.o $(BUILDDIR)/img.o
test-6: $(BUILDDIR)/test-6
$(BUILDDIR)/test-6: $(BUILDDIR)/test-6.o $(BUILDDIR)/img.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(BUILDDIR)
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)
