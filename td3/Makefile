CC := gcc
CFLAGS := -std=c99 -g -I$(HOMEBREW_PATH)/include -Iinclude -O3 -Wall
LDFLAGS := -limago -ljpeg -lpng -lfftw3 -lm

BUILDDIR = build
SRCDIR = src

DATADIR = images
RENDERDIR = renderings

.PHONY: all
all: test-glfip-1 test-glfip-2 test-glfip-3 test-glfip-4 test-rgbfip-4

.PHONY: $(BUILDDIR)
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

.PHONY: $(RENDERDIR)
$(RENDERDIR):
	@mkdir -p $(RENDERDIR)

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)

.PHONY: reset
reset:
	$(RM) -r $(BUILDDIR) $(RENDERDIR)

.PHONY: test
test: test-test-glfip-1 test-test-glfip-2 test-test-glfip-3 test-test-glfip-4 test-test-rgbfip-4

.PHONY: test-test-glfip-1 test-test-glfip-2 test-test-glfip-3 test-test-glfip-4 test-test-rgbfip-4
test-test-glfip-1: $(RENDERDIR)
	$(BUILDDIR)/test-glfip-1 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-1.png
	$(BUILDDIR)/test-glfip-1 -z $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-1-z.png
test-test-glfip-2: $(RENDERDIR)
	$(BUILDDIR)/test-glfip-2 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-2.png
	$(BUILDDIR)/test-glfip-2 -c $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-2-c.png
test-test-glfip-3: $(RENDERDIR)
	$(BUILDDIR)/test-glfip-3 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-3.png $(RENDERDIR)/mandrill-3-as.png $(RENDERDIR)/mandrill-3-ps.png
test-test-glfip-4: $(RENDERDIR)
	$(BUILDDIR)/test-glfip-4 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-4-0-5-0.png 0 5 0
	$(BUILDDIR)/test-glfip-4 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-4-0-30-0.png 0 30 0
	$(BUILDDIR)/test-glfip-4 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-4-0-30-1.png 0 30 1
	$(BUILDDIR)/test-glfip-4 $(DATADIR)/mandrill.png $(RENDERDIR)/mandrill-4-30-80-1.png 30 80 1
test-test-rgbfip-4: $(RENDERDIR)
	$(BUILDDIR)/test-rgbfip-4 $(DATADIR)/napoli.png $(RENDERDIR)/napoli-5-0-5-0.png 0 5 0
	$(BUILDDIR)/test-rgbfip-4 $(DATADIR)/napoli.png $(RENDERDIR)/napoli-5-1-20-1.png 1 20 1
	$(BUILDDIR)/test-rgbfip-4 $(DATADIR)/napoli.png $(RENDERDIR)/napoli-5-20-100-1.png 20 100 1

.PHONY: test-glfip-1 test-glfip-2 test-glfip-3 test-glfip-4 test-rgbfip-4
test-glfip-1: $(BUILDDIR)/test-glfip-1
test-glfip-2: $(BUILDDIR)/test-glfip-2
test-glfip-3: $(BUILDDIR)/test-glfip-3
test-glfip-4: $(BUILDDIR)/test-glfip-4
test-rgbfip-4: $(BUILDDIR)/test-rgbfip-4

$(BUILDDIR)/%: $(BUILDDIR)/%.o  $(BUILDDIR)/channel.o  $(BUILDDIR)/fip.o $(BUILDDIR)/fft.o
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ -c $<
