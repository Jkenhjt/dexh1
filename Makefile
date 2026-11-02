LIBNAME =             dexh1
STATIC_LIB :=         lib${LIBNAME}.a
SHARED_LIB :=         lib${LIBNAME}.so

SRC :=                $(wildcard src/*.c)
SRC_HEADERS :=        $(wildcard src/*.h)
OBJS :=               $(patsubst %.c, %.o, ${SRC})

PREFIX :=             /usr/local

BUILD_LIB_PATH :=     build/lib
BUILD_HEADERS_PATH := build/include

CFLAGS +=             -O3 -ffast-math
SAFEFLAGS :=          -Wall -Werror -pedantic -std=iso9899:1990


all: ${STATIC_LIB} ${SHARED_LIB} ${SRC_HEADERS} test

test: ${STATIC_LIB} ${SRC_HEADERS}
	${CC} ${LDFLAGS} ${CFLAGS} ${SAFEFLAGS} tests/test_request.c -L./build/lib -ldexh1 -I./build/include -static -o test_request
	./test_request

	${CC} ${LDFLAGS} ${CFLAGS} ${SAFEFLAGS} tests/test_response.c -L./build/lib -ldexh1 -I./build/include -static -o test_response
	./test_response

	rm test_request test_response

install: ${STATIC_LIB} ${SHARED_LIB}
	mkdir -p ${PREFIX}/include/${LIBNAME}

	cp -r ${BUILD_LIB_PATH}/${STATIC_LIB} ${BUILD_LIB_PATH}/${SHARED_LIB} ${PREFIX}/lib/
	cp -r ${SRC_HEADERS} ${PREFIX}/include/${LIBNAME}

uninstall:
	rm -rf ${PREFIX}/lib/${STATIC_LIB}
	rm -rf ${PREFIX}/lib/${SHARED_LIB}
	
	rm -rf ${PREFIX}/include/${LIBNAME}
	
${SRC_HEADERS}:
	mkdir -p ${BUILD_HEADERS_PATH}/${LIBNAME}
	cp -r ${SRC_HEADERS} ${BUILD_HEADERS_PATH}/${LIBNAME}

${STATIC_LIB}: ${OBJS}
	mkdir -p ${BUILD_LIB_PATH}

	ar rcs ${BUILD_LIB_PATH}/$@ ${OBJS}

	rm -rf ${OBJS}

%.o: %.c
	${CC} ${LDFLAGS} ${CFLAGS} ${SAFEFLAGS} -static -c $< -o $@

${SHARED_LIB}: ${SRC}
	mkdir -p ${BUILD_LIB_PATH}
	
	${CC} ${LDFLAGS} ${CFLAGS} ${SAFEFLAGS} -shared -fPIC -o ${BUILD_LIB_PATH}/$@ $^

clean:
	rm -rf ${OBJS} ./build

.PHONY: all clean install uninstall test
