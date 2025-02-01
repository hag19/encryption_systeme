# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 91.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi
CLIBS= -lm
DEFS= -DTEST
EXE= executable
OBJ= main.o\
     tree.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c tree.h
tree.o : tree.c tree.h

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(DEFS)

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)
