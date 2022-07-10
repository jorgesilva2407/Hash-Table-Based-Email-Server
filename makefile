CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin

OBJS = $(OBJ)/Home.o $(OBJ)/User.o $(OBJ)/List.o $(OBJ)/Server.o $(OBJ)/memlog.o
CFLAGS = -Wall -Werror -I include -std=c++17

EXE = $(BIN)/tp3.exe

$(EXE) : $(OBJS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)/main.cpp $(OBJS) -g

$(OBJ)/%.o : $(SRC)/%.c* $(INC)/%.h*
	$(CC) -o $@ -c $< $(CFLAGS)

clear:
	rm obj/*.o bin/*.exe