# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 95.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi
CLIBS= -lm
DEFS= 
EXE= executable
OBJ= main.o\
     point.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c point.h
point.o : point.c point.h

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(DEFS)

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)