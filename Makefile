OBJS = main.cpp Environment.cpp Symbol.cpp

CC = g++

COMPILER_FLAGS = -w

OBJ_NAME = "schemer"

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
