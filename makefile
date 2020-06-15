OBJS = ./src/*.cpp
CC = g++
#COMPILER_FLAGS = 
#LINKER_FLAGS = 
OBJ_NAME = randomizer

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
