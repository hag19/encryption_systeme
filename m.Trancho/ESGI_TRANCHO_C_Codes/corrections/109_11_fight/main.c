/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 109.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int min(int a, int b) {
  return (a < b) ? a : b;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

/* Nous définissons une structure représentant les stats d'un  */
/* personnage à un instant donné                               */
typedef struct Stats Stats;
struct Stats {
  int vie;
  int atk;
  int def;
  int vit;
};

/* Nous énumérons les différents stats définis plus haut. */
typedef enum {
  STI_VIE,
  STI_ATK,
  STI_DEF,
  STI_VIT,
  STI_NONE
} StatsId;

Stats Stats_creer(int vie, int atk, int def, int vit) {
  Stats stats = {vie, atk, def, vit};
  return stats;
}

/* Nous utilisons les stats précédemment donnés pour           */
/* sauvegarder des stats au début d'un combat et l'état        */
/* actuelle de ceux-cis. */
typedef struct Personnage Personnage;
struct Personnage {
  char nom[20];
  Stats base;
  Stats current;
};

/* Nous énumérons les sorts disponibles. */
typedef enum {
  SOI_COUP = 1,
  SOI_LOW_ATK,
  SOI_LOW_DEF,
  SOI_LOW_VIT,
  SOI_SOIN,
  SOI_UP_ATK,
  SOI_UP_DEF,
  SOI_UP_VIT
} SortId;

Personnage Personnage_creer(const char * nom, Stats base) {
  Personnage perso = {"", base, base};
  strcpy(perso.nom, nom);
  return perso;
}

void Personnage_fullheal(Personnage * perso) {
  perso->current = perso->base;
}

void Personnage_stat_mul(Personnage * perso, StatsId stat, double coeff) {
  switch(stat) {
    case STI_VIE : {
      perso->current.vie = min(perso->current.vie * coeff, perso->base.vie); 
    } break;
    case STI_ATK : perso->current.atk = max(perso->current.atk * coeff, 1); break;
    case STI_DEF : perso->current.def = max(perso->current.def * coeff, 1); break;
    case STI_VIT : perso->current.vit = max(perso->current.vit * coeff, 1); break;
    default : break;
  }
}

void Personnage_attacks_other(Personnage * tori, Personnage * uke) {
  uke->current.vie -= max(tori->current.atk / uke->current.def, 1);
  uke->current.vie = max(uke->current.vie, 0);
}

int Personnage_vivant(const Personnage * perso) {
  return perso->current.vie > 0;
}

void Personnages_afficher(const Personnage * first, const Personnage * second) {
  printf("%20s VS %s\n", first->nom, second->nom);
  printf(">>>>>>>>>>>>>>>>>>>> | <<<<<<<<<<<<<<<<<<<<\n");
  printf("Vie : %14d | Vie : %14d\n", first->current.vie, second->current.vie);
  printf("Attaque : %10d | Attaque : %10d\n", first->current.atk, second->current.atk);
  printf("Defense : %10d | Defense : %10d\n", first->current.def, second->current.def);
  printf("Vitesse : %10d | Vitesse : %10d\n", first->current.vit, second->current.vit);
  printf("---------------------+---------------------\n");
}

void afficher_sorts() {
  printf("1 . coup              5 . soin             \n");
  printf("2 . reduire attaque   6 . augmenter attaque\n");
  printf("3 . reduire defense   7 . augmenter defense\n");
  printf("4 . reduire vitesse   8 . augmenter vitesse\n");
  printf("---------------------+---------------------\n");
}

void Personnages_appliquer_sort(SortId id, Personnage * tori, Personnage * uke) {
  if(! Personnage_vivant(tori))
    return;
  switch(id) {
    case SOI_COUP : {
      Personnage_attacks_other(tori, uke);
      printf("%s attaque %s.\n", tori->nom, uke->nom);
    } break;
    case SOI_LOW_ATK : {
      Personnage_stat_mul(uke, STI_ATK, 0.8);
      printf("L'attaque de %s diminue.\n", uke->nom);
    } break;
    case SOI_LOW_DEF : {
      Personnage_stat_mul(uke, STI_DEF, 0.6);
      printf("La defense de %s diminue.\n", uke->nom);
    } break;
    case SOI_LOW_VIT : {
      Personnage_stat_mul(uke, STI_VIT, 0.5);
      printf("La vitesse de %s diminue.\n", uke->nom);
    } break;
    case SOI_SOIN : {
      Personnage_stat_mul(tori, STI_VIE, 1.2);
      printf("%s se soigne.\n", tori->nom);
    } break;
    case SOI_UP_ATK : {
      Personnage_stat_mul(tori, STI_ATK, 1.4);
      printf("L'attaque de %s augmente.\n", tori->nom);
    } break;
    case SOI_UP_DEF : {
      Personnage_stat_mul(tori, STI_DEF, 1.2);
      printf("La defense de %s augmente.\n", tori->nom);
    } break;
    case SOI_UP_VIT : {
      Personnage_stat_mul(tori, STI_VIT, 1.1);
      printf("La vitesse de %s augmente.\n", tori->nom);
    } break;
    default : break;
  }
}

int main() {
  Personnage joueur = Personnage_creer("Joueur", Stats_creer(100, 50, 20, 100));
  Personnage adversaire = Personnage_creer("Adversaire", Stats_creer(100, 50, 20, 100));
  SortId joueurSort;
  SortId advSort;
  int id;
  
  do {
    Personnages_afficher(&joueur, &adversaire);
    afficher_sorts();
    printf("Votre sort : ");
    scanf("%d", &id);
    joueurSort = id;
    advSort = (rand() % 2 == 1) ? 1 : 1 + (rand() % 8);
    if(joueur.current.vit >= adversaire.current.vit) {
      Personnages_appliquer_sort(joueurSort, &joueur, &adversaire);
      Personnages_appliquer_sort(advSort, &adversaire, &joueur);
    } else {
      Personnages_appliquer_sort(advSort, &adversaire, &joueur);
      Personnages_appliquer_sort(joueurSort, &joueur, &adversaire);
    }
  } while(Personnage_vivant(&joueur) && Personnage_vivant(&adversaire));
  
  if(Personnage_vivant(&joueur)) {
    printf("Bravo, vous sortez vainqueur du combat.\n");
  } else {
    printf("Votre adversaire gagne, essayez encore.\n");
  }
  
  exit(EXIT_SUCCESS);
}