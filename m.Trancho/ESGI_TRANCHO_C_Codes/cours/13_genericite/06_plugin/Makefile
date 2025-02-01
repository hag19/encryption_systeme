# ------------------------------------------
# ESGI : Cours de Langage C de Kevin TRANCHO.
# Code d'illustration de concept.
# ------------------------------------------

executable :
	gcc -c src/esgilib.c -fPIC
	gcc -o libesgi.so esgilib.o -shared
	gcc -o executable src/main.c -ldl

view :
	nm -D libesgi.so
	ldd executable

clean :
	rm -rf executable
	rm -rf libesgi.so esgilib.o