# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -g -Wno-unused-result -Wall -ansi -I./include
CLIBS= -lm -lgmp
EXE= executable
OBJ= obj/
SRC= src/
INCL= include/
FILEC:= $(wildcard $(SRC)*.c)
FILEH:= $(wildcard $(INCL)*.h)
FILEO:= $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(INCL)%.h
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

run : $(EXE)
	./$(EXE)

debug : $(EXE)
	gdb ./$(EXE)

memory : $(EXE)
	valgrind ./$(EXE)

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)
	rm -rf $(EXE) 