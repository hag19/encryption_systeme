/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Code d'illustration de concept.
 */

/*#include <esgilib.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
  const char * lib_path = "libesgi.so";
  void (*ESGI_init)() = NULL;
  void (*ESGI_quit)() = NULL;
  
  void * dlptr = NULL;
  if((dlptr = dlopen(lib_path, RTLD_NOW)) == NULL) {
    fprintf(stderr, "Erreur d'ouverture du plugin \"%s\"\n%s\n", lib_path, dlerror());
  }
  if((ESGI_init = (void (*)())dlsym(dlptr, "ESGI_init")) == NULL) {
    dlclose(dlptr);
    fprintf(stderr, "Erreur de lecture de \"ESGI_init\" du plugin \"%s\"\n%s\n", lib_path, dlerror());
    exit(EXIT_FAILURE);
  }
  if((ESGI_quit = (void (*)())dlsym(dlptr, "ESGI_quit")) == NULL) {
    dlclose(dlptr);
    fprintf(stderr, "Erreur de lecture de \"ESGI_quit\" du plugin \"%s\"\n%s\n", lib_path, dlerror());
    exit(EXIT_FAILURE);
  }
  
  ESGI_init();
  ESGI_quit();
  
  dlclose(dlptr);
  dlptr = NULL;
  exit(EXIT_SUCCESS);
}