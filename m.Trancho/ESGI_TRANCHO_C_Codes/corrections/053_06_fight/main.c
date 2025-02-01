/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 53.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Statistiques générales en début d'une partie : */

int max_vie = 100;
int start_atk = 50;
int start_def = 20;

/* Statistiques du joueur : */

int self_vie;
int self_atk;
int self_def;

/* Statistiques de l'adversaire : */

int adv_vie;
int adv_atk;
int adv_def;

/* Ici l'utilisation de variables globales se justifie par le  */
/* besoin de séparer en fonctions, mais le manque de           */
/* connaissances à l'étape actuelle du cours pour modifier     */
/* plusieurs variables avec des pointeurs / renvoyer plusieurs */
/* valeurs.                                                    */

/* Mise aux valeurs initiales des statistiques des deux        */
/* joueurs.                                                    */
void init() {
  self_vie = max_vie;
  self_atk = start_atk;
  self_def = start_def;
  
  adv_vie = max_vie;
  adv_atk = start_atk;
  adv_def = start_def;
}

/* Fonction générale pour calculer les dégats d'une attaque. */
int degats(int tori_atk, int uke_def) {
  int res = tori_atk / uke_def;
  if(res < 1) {
    res = 1;
  }
  return res;
}

/* Fonction générale pour appliquer un buff : en pourcentage */
int boost(int value, int pourcentage) {
  value = ((long)(100 + pourcentage) * value) / 100;
  if(value < 1) {
    value = 1;
  }
  return value;
}

/* Fonctions relatives au joueur : */

void self_regen() {
  self_vie += 0.25 * max_vie;
  if(self_vie > max_vie) {
    self_vie = max_vie;
  }
}

void self_hit() {
  adv_vie -= degats(self_atk, adv_def);
}

void self_boost_atk() {
  self_atk = boost(self_atk, 20);
}

void self_boost_def() {
  self_def = boost(self_def, 30);
}

void self_action(int id) {
  switch(id) {
    case 1 : {
      printf("Le joueur cogne l\' adversaire.\n");
      self_hit();
    } break;
    
    case 2 : {
      printf("Le joueur se soigne.\n");
      self_regen();
    } break;
    
    case 3 : {
      printf("Le joueur augmente son attaque.\n");
      self_boost_atk();
    } break;
    
    case 4 : {
      printf("Le joueur augmente sa defense.\n");
      self_boost_def();
    } break;
  }
}

/* Par manque de généricité et l'utilisation de variables      */
/* globales, le code est dupliqué :                            */

/* Fonctions relatives à l'adversaire : */

void adv_regen() {
  adv_vie += 0.25 * max_vie;
  if(adv_vie > max_vie) {
    adv_vie = max_vie;
  }
}

void adv_hit() {
  self_vie -= degats(adv_atk, self_def);
}

void adv_boost_atk() {
  adv_atk = boost(adv_atk, 20);
}

void adv_boost_def() {
  adv_def = boost(adv_def, 30);
}

void adv_action(int id) {
  switch(id) {
    case 1 : {
      printf("L\'adversaire cogne le joueur.\n");
      adv_hit();
    } break;
    
    case 2 : {
      printf("L\'adversaire se soigne.\n");
      adv_regen();
    } break;
    
    case 3 : {
      printf("L\'adversaire augmente son attaque.\n");
      adv_boost_atk();
    } break;
    
    case 4 : {
      printf("L\'adversaire augmente sa defense.\n");
      adv_boost_def();
    } break;
  }
}

/* Affichage du jeu : */

void display_actions() {
  printf(" 1 - cogner.\n"
         " 2 - se soigner.\n"
         " 3 - augmenter attaque.\n"
         " 4 - augmenter defense.\n");
}

void display() {
  printf("+-------------------+-------------------+\n");
  printf("|      Joueur       |     Adversaire    |\n");
  printf("+-------------------+-------------------+\n");
  printf("| Vie : %11d | Vie : %11d |\n", self_vie, adv_vie);
  printf("| Attaque : %7d | Attaque : %7d |\n", self_atk, adv_atk);
  printf("| Defense : %7d | Defense : %7d |\n", self_def, adv_def);
  printf("+-------------------+-------------------+\n");
}

/* Un combat : */

int main() {
  int self_choix;
  int adv_choix;
  srand(time(NULL));
  init();
  while(self_vie > 0 && adv_vie > 0) {
    display();
    display_actions();
    printf("Votre choix : ");
    scanf("%d", &self_choix);
    adv_choix = 1;
    if(rand() % 2 == 0) {
      adv_choix = 2 + rand() % 3;
    }
    self_action(self_choix);
    adv_action(adv_choix);
  }
  if(self_vie <= 0 && adv_vie <= 0) {
    printf("Match nul.\n");
  } else if(self_vie > 0) {
    printf("Victoire du joueur.\n");
  } else {
    printf("Defaite du joueur.\n");
  }
  exit(EXIT_SUCCESS);
}