CC=g++
INCLUDE_DIR := ${MNIST_ML_ROOT}/include
SRC := ${MNIST_ML_ROOT}/include
CFLAGS := -shared -std=c++11 -g
LIB_DATA := libdata.so

akk L ${LIB_DATA}

${LIB_DATA} : libdir objdir obj/data_handler.o obj.data.o
	${CC} ${CFLAGS} -o ${MNIST_ML_ROOT}/lib/${LIB_DATA} obj/*.o
	rm -r ${MNIST_ML_ROOT}/obj

libdir :
	mkdir -p ${MNIST_ML_ROOT}/lib

objdir :
	mkdir -p ${MNIST_ML_ROOT}/obj

obj/data_handler.o: ${SRC}/data_handler.hpp
	${CC} -fPIC ${CFLAGS} -o obj/data_handler.o -I${INCLUDE_DIR} -c ${SRC}/data_handler.hpp

obj/data.o: ${SRC}/data.hpp
	${CC} -fPIC ${CFLAGS} -o obj/data.o -I${INCLUDE_DIR} -c ${SRC}/data.hpp

clean:
	rm -r ${MNIST_ML_ROOT}/lib
	rm -r ${MNIST_ML_ROOT}/obj