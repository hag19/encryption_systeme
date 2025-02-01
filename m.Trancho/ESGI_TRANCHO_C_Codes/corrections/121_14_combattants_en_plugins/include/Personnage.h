/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#ifndef DEF_HEADER_PERSONNAGE
#define DEF_HEADER_PERSONNAGE

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

typedef struct Stats Stats;
struct Stats {
  int vie;
  int atk;
  int def;
  int vit;
};

typedef struct Personnage Personnage;
struct Personnage {
  char nom[21];
  Stats start;
  Stats current;
  void (*coups[4])(Personnage *, Personnage *);
  int (*choix)(const Personnage *, const Personnage *);
  LIBTYPE dlptr;
};

Personnage Personnage_charger(const char * path);

void Personnage_keep_in_bounds(Personnage * perso);

void Personnage_init(Personnage * perso);

void Personnage_quit(Personnage * perso);

void Personnage_display(const Personnage * perso);

int Personnage_est_vivant(const Personnage * perso);

const char * Personnage_nom(const Personnage * perso);

int Personnage_est_plus_rapide(const Personnage * self, const Personnage * other);

void Personnage_action(Personnage * self, Personnage * other);

Personnage Personnage_default_soldier();

Personnage Personnage_defensive_soldier();

#endif