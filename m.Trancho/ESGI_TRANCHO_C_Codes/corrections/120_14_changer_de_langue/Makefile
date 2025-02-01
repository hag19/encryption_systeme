# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Correction de l'exercice 98.
# ------------------------------------------

ifdef OS # Windows' case
LDL= 
else
LDL= -ldl
endif

executable :
	gcc -o executable main.c $(LDL)
	gcc -c fr.c -fPIC
	gcc -c en.c -fPIC
ifdef OS # Windows' case
	gcc -shared -o fr.dll fr.o
	gcc -shared -o en.dll en.o
else
	gcc -shared -o fr.so fr.o
	gcc -shared -o en.so en.o
endif
	rm fr.o
	rm en.o

clean :
	rm executable
ifdef OS # Windows' case
	rm fr.dll en.dll
else
	rm fr.so en.so
endif