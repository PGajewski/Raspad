DIR_FONTS = ./Fonts
DIR_OBJ = ./src
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_CXX = $(wildcard ${DIR_OBJ}/*.cpp)


OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = gajos_raspad_app
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc-8.1.0

CXX = g++-8.1.0

CFLAGS += -Wall

DEBUG = -g -DDEBUG -O0

CXXFLAGS = -std=c++17 -Wall

OP_FLAG = -O3

LIB = -lbcm2835
CXXLIB = -I/usr/include/opencv2 -I/usr/include/glib-2.0  -pthread -lstdc++fs -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio


${TARGET}:${OBJ_O}
	$(CXX) $(CXXFLAGS) $(OBJ_CXX)  -o $@ $(OBJ_O) $(LIB) $(CXXLIB)

${DIR_BIN}/%.o:$(DIR_OBJ)/%.c
	$(CC) $(OP_FLAG)  $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(OP_FLAG) $(CFLAGS) -c  $< -o $@ $(LIB)

clean :
	rm $(DIR_BIN)/*.*
	rm $(TARGET)

optimal : ${OBJ_O}
	$(CXX) $(CXXFLAGS) $(OP_FLAG) $(OBJ_CXX) -o $(TARGET) $(OBJ_O) $(LIB) $(CXXLIB)

debug : CXXFLAGS += $(DEBUG)
debug :	CFLAGS += $(DEBUG)
debug : OPT_FLAG = -O0

debug : ${OBJ_O}
	$(CXX) $(CXXFLAGS) $(OP_FLAG) $(OBJ_CXX) -o $(TARGET) $(OBJ_O) $(LIB) $(CXXLIB)
