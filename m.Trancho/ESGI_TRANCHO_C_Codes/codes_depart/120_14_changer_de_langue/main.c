#include <stdio.h>
#include <stdlib.h>

typedef struct Langage Langage;
struct Langage {
  void (*saluer)();
  void (*quit)();
};

int main(int argc, char * argv[]) {
  const char * lang_path = argc > 1 ? argv[1] : "fr.so";
  Langage lang = Langage_charger(lang_path);
  lang.saluer();
  lang.quit();
  Langage_liberer(&lang);
  exit(EXIT_SUCCESS);
}