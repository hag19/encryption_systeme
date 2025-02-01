# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -g -Wall -Werror -ansi -Wno-unused-result -I./include -Wl,--export-dynamic
CLIBS= -lm -lSDL -lSDL_gfx -ldl
EXE= executable
OBJ= obj/
SRC= src/
INCL= include/
PLUG= plugins/
LIB= extensions/
FILEC:= $(wildcard $(SRC)*.c)
FILEH:= $(wildcard $(INCL)*.h)
FILEO:= $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))
FILEP:= $(wildcard $(PLUG)*.c)
FILEL:= $(patsubst $(PLUG)%.c,$(LIB)%.so,$(FILEP))

$(EXE) : $(FILEO) $(FILEL)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(INCL)%.h
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<
	
$(LIB)%.so : $(PLUG)%.c
	@if [ ! -d "$(LIB)" ]; then mkdir $(LIB); fi;
	$(CC) $(CFLAGS) -o tmp.o -c $< -fPIC
	$(CC) -shared $(CFLAGS) -o $@ tmp.o $(CLIBS)
	rm -rf tmp.o

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
	rm -rf $(LIB)*.so
	rm -rf $(LIB)
