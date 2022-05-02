TARGET := img-fourier-tool
DEPS := img-pixmap fft fip

BUILD_DIR := build
INCLUDE_DIR := include
SRC_DIR := src

CC := clang
CFLAGS := -O3 -I/usr/local/include -I${HOMEBREW_PATH}/include -I${INCLUDE_DIR} -g -Wall
LDFLAGS := -L/usr/local/lib -L${HOMEBREW_PATH}/lib -limago -ljpeg -lpng -lfftw3 -lm

.PHONY: install
install: build
	@cp ${BUILD_DIR}/${TARGET} .
	@${RM} -r ${BUILD_DIR}

.PHONY: build
build: ${TARGET}

.PHONY: ${TARGET}
${TARGET}: ${BUILD_DIR}/${TARGET}

${BUILD_DIR}/${TARGET}: $(addprefix ${BUILD_DIR}/, $(addsuffix .o, ${DEPS})) ${BUILD_DIR}/${TARGET}.o
	${CC} ${LDFLAGS} -o $@ $^

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} -o $@ -c $^

.PHONY: clean
clean:
	@${RM} -r ${BUILD_DIR} ${TARGET}
