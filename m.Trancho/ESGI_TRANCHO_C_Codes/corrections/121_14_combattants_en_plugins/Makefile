# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 99.
# ------------------------------------------

CC= gcc
CFLAGS= -O2 -Wall -Werror -ansi
ifdef OS # Windows' case
LDL= 
else
LDL= -ldl
endif
CLIBS= -lm $(LDL)
EXE= executable
OBJ= obj/
SRC= src/
INCL= include/
PLUGC= plugins/src/
PLUGL= plugins/lib/
FILEC:= $(wildcard $(SRC)*.c)
FILEH:= $(wildcard $(INCL)*.h)
FILEO:= $(patsubst $(SRC)%.c,$(OBJ)%.o,$(FILEC))
FILEPC:= $(wildcard $(PLUGC)*.c)
ifdef OS # Windows' case
FILEPL:= $(patsubst $(PLUGC)%.c,$(PLUGL)%.dll,$(FILEPC))
DFLAGS= -Wl,--export-all-symbols -Wl,--enable-auto-import
else
FILEPL:= $(patsubst $(PLUGC)%.c,$(PLUGL)%.so,$(FILEPC))
DFLAGS= -Wl,--export-dynamic
endif

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(DFLAGS) $(CLIBS)

$(OBJ)main.o : $(SRC)main.c $(FILEH)
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o : $(SRC)%.c $(INCL)%.h
	@if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi;
	$(CC) $(CFLAGS) -o $@ -c $<
	
plugin :
	@if [ ! -d "$(PLUGL)" ]; then mkdir $(PLUGL); fi;
	echo "Generation of plugins"
	for i in `ls $(PLUGC)*.c`; do $(CC) $(CFLAGS) -c $$i -fPIC ; done
ifdef OS # Windows' case
	for i in `ls *.o`; do $(CC) $(CFLAGS) -shared -o $(PLUGL)$${i%%.*}.dll $$i $(CLIBS); done
else
	for i in `ls *.o`; do $(CC) $(CFLAGS) -shared -o $(PLUGL)$${i%%.*}.so $$i $(CLIBS); done
endif
	rm -rf *.o

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)
	rm -rf $(EXE)

mrproper : clean
	rm -rf $(PLUGO)*.o
	rm -rf $(PLUGO)
ifdef OS # Windows' case
	rm -rf $(PLUGL)*.dll
else
	rm -rf $(PLUGL)*.so
endif