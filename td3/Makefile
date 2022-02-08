CC := gcc
CFLAGS := -std=c99 -g -I$(HOMEBREW_PATH)/include -Iinclude -O3 -Wall
LDFLAGS := -limago -ljpeg -lpng -lfftw3 -lm

OUTDIR = build
SRCDIR = src

.PHONY: all
all: test-glfip-1 test-glfip-2 test-glfip-3 # test-glfip-4

.PHONY: test-glfip-1 test-glfip-2 test-glfip-3 test-glfip-4
test-glfip-1: $(OUTDIR)/test-glfip-1
test-glfip-2: $(OUTDIR)/test-glfip-2
test-glfip-3: $(OUTDIR)/test-glfip-3
test-glfip-4: $(OUTDIR)/test-glfip-4

$(OUTDIR)/%: $(OUTDIR)/%.o $(OUTDIR)/fft.o  $(OUTDIR)/fip.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OUTDIR)/%.o: $(SRCDIR)/%.c outdir
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: outdir
outdir:
	@mkdir -p $(OUTDIR)

.PHONY: clean
clean:
	$(RM) -r $(OUTDIR)
