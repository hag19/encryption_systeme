/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 120.
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32 /* Windows' version of direct library */
#include <windows.h>
#define LIBTYPE HINSTANCE
#define OPENLIB(libname) LoadLibraryW(libname)
#define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
#else
#include <dlfcn.h>
#define LIBTYPE void*
#define OPENLIB(libname) dlopen((libname), RTLD_NOW)
#define LIBFUNC(lib, fn) dlsym((lib), (fn))
#endif

typedef struct Langage Langage;
struct Langage {
  void (*saluer)();
  void (*quit)();
  LIBTYPE dlptr;
};

Langage Langage_charger(const char * path) {
  LIBTYPE dlptr = NULL;
  Langage lang;

#ifndef _WIN32
	if((dlptr = OPENLIB(path)) == NULL) {
		fprintf(stderr, "Erreur d'ouverture du plugin \"%s\"\n%s\n", path, dlerror());
#else
	wchar_t wfile[256];
	mbstowcs(wfile, path, strlen(path) + 1);
	if((dlptr = OPENLIB(wfile)) == NULL) {
		fprintf(stderr, "Erreur d'ouverture du plugin \"%s\"\n", path);
#endif
    exit(EXIT_FAILURE);
  }
  if((lang.saluer = (void (*)())LIBFUNC(dlptr, "saluer")) == NULL) {
#ifndef _WIN32
    dlclose(dlptr);
    fprintf(stderr, "Erreur de lecture de \"saluer\" du plugin \"%s\"\n%s\n", path, dlerror());
#endif
    exit(EXIT_FAILURE);
  }
  if((lang.quit = (void (*)())LIBFUNC(dlptr, "quit")) == NULL) {
#ifndef _WIN32
    dlclose(dlptr);
    fprintf(stderr, "Erreur de lecture de \"quit\" du plugin \"%s\"\n%s\n", path, dlerror());
#endif
    exit(EXIT_FAILURE);
  }
  printf("Chargement de la langue depuis \"%s\"\n", path);
  lang.dlptr = dlptr;
  return lang;
}

void Langage_liberer(Langage * lang) {
  if(lang->dlptr) {
#ifndef _WIN32
    dlclose(lang->dlptr);
#endif
    lang->dlptr = NULL;
  }
}

int main(int argc, char * argv[]) {
#ifdef _WIN32
  const char * lang_path = argc > 1 ? argv[1] : "fr.dll";
#else
  const char * lang_path = argc > 1 ? argv[1] : "fr.so";
#endif
  Langage lang = Langage_charger(lang_path);
  lang.saluer();
  lang.quit();
  Langage_liberer(&lang);
  exit(EXIT_SUCCESS);
}