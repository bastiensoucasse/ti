LDFLAGS = -limago -lpng -ljpeg

BUILD_DIR = build
SRC_DIR = src

.PHONY: all
all: img-comp img-convert img-decomp img-format img-gummira img-rotchan

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/decomp.o: $(SRC_DIR)/%.c $(SRC_DIR)/tools.c
$(BUILD_DIR)/comp.o: $(SRC_DIR)/%.c $(SRC_DIR)/tools.c

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $<

%: $(BUILD_DIR)/%.o
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/$@ $<
