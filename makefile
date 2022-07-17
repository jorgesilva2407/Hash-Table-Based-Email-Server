CC = g++
SRC = src
OBJ = obj
DBG = debug
GRC = gerador_de_carga
OUT = out
INC = include
BIN = bin

OBJS = $(OBJ)/Home.o $(OBJ)/User.o $(OBJ)/List.o $(OBJ)/Server.o $(OBJ)/memlog.o
CFLAGS = -Wall -I include -std=c++17

EXE = $(BIN)/tp3.exe

$(EXE) : $(OBJS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)/main.cpp $(OBJS) -g

$(OBJ)/%.o : $(SRC)/%.c* $(INC)/%.h*
	$(CC) -o $@ -c $< $(CFLAGS)

test:
	$(EXE) -i $(GRC)/test1.txt -o $(OUT)/test1.out
	cat memLog.out
	$(EXE) -i $(GRC)/test2.txt -o $(OUT)/test2.out
	cat memLog.out
	$(EXE) -i $(GRC)/test3.txt -o $(OUT)/test3.out
	cat memLog.out
	$(EXE) -i $(GRC)/test4.txt -o $(OUT)/test4.out
	cat memLog.out
	$(EXE) -i $(GRC)/test5.txt -o $(OUT)/test5.out
	cat memLog.out
	$(EXE) -i $(GRC)/test6.txt -o $(OUT)/test6.out
	cat memLog.out
	$(EXE) -i $(GRC)/test7.txt -o $(OUT)/test7.out
	cat memLog.out
	$(EXE) -i $(GRC)/test8.txt -o $(OUT)/test8.out
	cat memLog.out
	$(EXE) -i $(GRC)/test9.txt -o $(OUT)/test9.out
	cat memLog.out
	$(EXE) -i $(GRC)/test10.txt -o $(OUT)/test10.out
	cat memLog.out

copy:
	cp $(SRC)/* $(DBG)
	cp $(INC)/* $(DBG)

clear:
	rm $(OBJ)/*.o $(BIN)/*.exe $(OUT)/*