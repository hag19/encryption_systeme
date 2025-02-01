# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 94.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi
CLIBS= -lm
DEFS= 
EXE= executable
OBJ= main.o\
     bitbuffer.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c bitbuffer.h
tree.o : bitbuffer.c bitbuffer.h

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(DEFS)

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)
