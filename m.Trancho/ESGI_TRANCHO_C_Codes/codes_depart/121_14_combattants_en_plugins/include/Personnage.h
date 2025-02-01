#ifndef DEF_HEADER_PERSONNAGE
#define DEF_HEADER_PERSONNAGE

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef struct Stats Stats;
struct Stats {
  int vie; /* vie */
  int atk; /* attaque */
  int def; /* defense */
  int vit; /* vitesse */
};

typedef struct Personnage Personnage;
struct Personnage {
  char nom[21]; /* nom du personnage. */
  Stats start; /* statistiques initiales. */
  Stats current; /* statistiques courrantes. */
  void (*coups[4])(Personnage *, Personnage *); /* capacités du personnage. */
  int (*choix)(const Personnage *, const Personnage *); /* choix de la capacité selon la configuration. */
  void * dlptr; /* référence vers bibliothèque dynamique associée. */
};

/* Charge un personnage depuis un fichier .so */
Personnage Personnage_charger(const char * path);

/* Replace les valeurs courantes en fonction des valeurs */
/* initiales si nécessaire. */
void Personnage_keep_in_bounds(Personnage * perso);

/* Initialise le personnage à ses stats initiaux. */
void Personnage_init(Personnage * perso);

/* Ferme la bibliothèque dynamique ouverte. */
void Personnage_quit(Personnage * perso);

/* Affiche le personnage. */
void Personnage_display(const Personnage * perso);

/* Indique si le personnage est vivant. */
int Personnage_est_vivant(const Personnage * perso);

/* Donne le nom du personnage. */
const char * Personnage_nom(const Personnage * perso);

/* Indique si le personnage est plus rapide que l'autre. */
int Personnage_est_plus_rapide(const Personnage * self, const Personnage * other);

/* Effectue l'action associée au personnage. */
void Personnage_action(Personnage * self, Personnage * other);

/* Donne un soldat simple. */
Personnage Personnage_default_soldier();

/* Donne un garde. */
Personnage Personnage_defensive_soldier();

#endif