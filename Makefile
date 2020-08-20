OBJS = ./src/main.cc ./src/chip8.cc

CC = g++

COMPILER_FLAGS = -Wall

LINKER_FLAGS = -lSDL2 -lSDL2_ttf

OBJ_NAME = ./bin/chipate

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
