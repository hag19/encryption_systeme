# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 100.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Werror -ansi
CLIBS= -lm
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

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)
	rm -rf $(EXE) 