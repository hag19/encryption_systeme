/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 121.
 */

#include "../include/Personnage.h"

#include "../include/Spell.h"
#include "../include/AI.h"

#include <string.h>

Personnage Personnage_charger(const char * path) {
  LIBTYPE dlptr = NULL;
  Personnage (*instantiate)() = NULL;
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
  if((instantiate = (Personnage (*)())LIBFUNC(dlptr, "Personnage_instantiate")) == NULL) {
#ifndef _WIN32
    dlclose(dlptr);
    fprintf(stderr, "Erreur de lecture de \"Personnage_instantiate\" du plugin \"%s\"\n%s\n", path, dlerror());
#else
    fprintf(stderr, "Erreur de lecture de \"Personnage_instantiate\" du plugin \"%s\"\n", path);
#endif
    exit(EXIT_FAILURE);
  }
  fprintf(stderr, "Lecture de \"Personnage_instantiate\" du plugin \"%s\"\n", path);
  Personnage perso = instantiate();
  fprintf(stderr, "Personnage instancié\n");
  perso.dlptr = dlptr;
  return perso;
}

void Personnage_keep_in_bounds(Personnage * perso) {
  if(perso->current.vie < 0) {
    perso->current.vie = 0;
  }
  if(perso->current.atk < 1) {
    perso->current.atk = 1;
  }
  if(perso->current.def < 1) {
    perso->current.def = 1;
  }
  if(perso->current.vit < 1) {
    perso->current.vit = 1;
  }
  if(perso->current.vie > perso->start.vie) {
    perso->current.vie = perso->start.vie;
  }
  if(perso->current.atk > 1000 * perso->start.atk) {
    perso->current.atk = 1000 * perso->start.atk;
  }
  if(perso->current.def > 1000 * perso->start.def) {
    perso->current.def = 1000 * perso->start.def;
  }
  if(perso->current.vit > 1000 * perso->start.vit) {
    perso->current.vit = 1000 * perso->start.vit;
  }
}

void Personnage_init(Personnage * perso) {
  perso->current = perso->start;
}

void Personnage_quit(Personnage * perso) {
  if(perso->dlptr) {
#ifndef _WIN32
    dlclose(perso->dlptr);
#endif
    perso->dlptr = NULL;
  }
}

void Personnage_display(const Personnage * perso) {
  printf("+----------------------+\n");
  printf("| %20s |\n", perso->nom);
  printf("| vie : %14d |\n", perso->current.vie);
  printf("| atk : %14d |\n", perso->current.atk);
  printf("| def : %14d |\n", perso->current.def);
  printf("| vit : %14d |\n", perso->current.vit);
  printf("+----------------------+\n");
}

int Personnage_est_vivant(const Personnage * perso) {
  return perso->current.vie > 0;
}

const char * Personnage_nom(const Personnage * perso) {
  return perso->nom;
}

int Personnage_est_plus_rapide(const Personnage * self, const Personnage * other) {
  return self->current.vit >= other->current.vit;
}

void Personnage_action(Personnage * self, Personnage * other) {
  int choix = self->choix(self, other);
  self->coups[choix](self, other);
}

Personnage Personnage_default_soldier() {
  return (Personnage) {
    .nom = "Soldat",
    .start = (Stats) {
      .vie = 100,
      .atk = 50,
      .def = 50,
      .vit = 10
    },
    .coups = {
      &Spell_coup_simple,
      &Spell_se_soigner,
      &Spell_boost_atk,
      &Spell_boost_def
    },
    .choix = &AI_hit_prior,
    .dlptr = NULL
  };
}

Personnage Personnage_defensive_soldier() {
  return (Personnage) {
    .nom = "Garde",
    .start = (Stats) {
      .vie = 120,
      .atk = 30,
      .def = 70,
      .vit = 10
    },
    .coups = {
      &Spell_coup_simple,
      &Spell_se_soigner,
      &Spell_boost_atk,
      &Spell_boost_def
    },
    .choix = &AI_buff_prior,
    .dlptr = NULL
  };
}