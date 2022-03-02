CC := clang
CFLAGS := -std=c17 -O3 -Wall -Iinclude -I$(HOMEBREW_PATH)/include
LDFLAGS := -L$(HOMEBREW_PATH)/lib -limago -ljpeg -lpng -lfftw3 -lm

BUILDDIR := build
SRCDIR := src

DATADIR := images

.PHONY: all
all: test-hist # test-lhist # test-stif # test-lstif # test-threshold # al-blur # al-thresh # al-enhance # lms-img

.PHONY: test-hist
test-hist: $(BUILDDIR)/test-hist
$(BUILDDIR)/test-hist: $(BUILDDIR)/test-hist.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: test-lhist
test-lhist: $(BUILDDIR)/test-lhist
$(BUILDDIR)/test-lhist: $(BUILDDIR)/test-lhist.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: test-stif
test-stif: $(BUILDDIR)/test-stif
$(BUILDDIR)/test-stif: $(BUILDDIR)/test-stif.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: test-lstif
test-lstif: $(BUILDDIR)/test-lstif
$(BUILDDIR)/test-lstif: $(BUILDDIR)/test-lstif.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: test-threshold
test-threshold: $(BUILDDIR)/test-threshold
$(BUILDDIR)/test-threshold: $(BUILDDIR)/test-threshold.o $(BUILDDIR)/threshold.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: al-blur
al-blur: $(BUILDDIR)/al-blur
$(BUILDDIR)/al-blur: $(BUILDDIR)/al-blur.o $(BUILDDIR)/threshold.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: al-thresh
al-thresh: $(BUILDDIR)/al-thresh
$(BUILDDIR)/al-thresh: $(BUILDDIR)/al-thresh.o $(BUILDDIR)/threshold.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: al-enhance
al-enhance: $(BUILDDIR)/al-enhance
$(BUILDDIR)/al-enhance: $(BUILDDIR)/al-enhance.o $(BUILDDIR)/threshold.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

.PHONY: lms-img
lms-img: $(BUILDDIR)/lms-img
$(BUILDDIR)/lms-img: $(BUILDDIR)/lms-img.o $(BUILDDIR)/threshold.o $(BUILDDIR)/stif.o $(BUILDDIR)/histogram.o $(BUILDDIR)/bbox.o $(BUILDDIR)/img.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: $(BUILDDIR)
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	$(RM) -r $(BUILDDIR)
