# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 90.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi
CLIBS= -lm
DEFS= -DBENCHMARKS
EXE= executable
OBJ= main.o\
     arraylist.o\
     hashmap.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c arraylist.h hashmap.h
arraylist.o : arraylist.c arraylist.h
hashmap.o : hashmap.c hashmap.h

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(DEFS)

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)