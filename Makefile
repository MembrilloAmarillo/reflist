CC = clang++

INC_DIR 	= ./include
EXT_DIR 	= ./external/AAED/
SRC_DIR		= ./src
OBJ_DIR  	= ./obj
BUILD_DIR 	= ./build

INC = ${INC_DIR}/parser.h ${INC_DIR}/lexer.h \
	  ${EXT_DIR}/TAD/lista_enla_cab.h \
	  ${INC_DIR}/my_string.h

SRC = ${SRC_DIR}/main.cpp ${SRC_DIR}/parser.cpp \
	  ${SRC_DIR}/lexer.cpp ${SRC_DIR}/my_string.cpp

OBJ = ${OBJ_DIR}/main.o ${OBJ_DIR}/parser.o \
	  ${OBJ_DIR}/lexer.o ${OBJ_DIR}/my_string.o

CXXFLAGS := -I${INC_DIR} -I${EXT_DIR} -std=c++11 -Wall -Werror -pedantic-errors \
		   -Wextra -Wconversion -Wformat -Wparentheses  

debug=0
ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

LIBS = -lstdc++

TARGET = ${BUILD_DIR}/parser

all: ${TARGET}

${TARGET} : ${OBJ}
	@mkdir -p $(BUILD_DIR)
	${CC} ${CXXFLAGS} -o $@ $^ ${LIBS}

./obj/%.o : ${SRC_DIR}/%.cpp
	@mkdir -p $(OBJ_DIR)
	${CC} ${CXXFLAGS} -c -o $@ $< 

.PHONY : clean

clean:
	${RM} ${RMFLAGS} ${BUILD_DIR}/* ${OBJ_DIR}/*.o 
