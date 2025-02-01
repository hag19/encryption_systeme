/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 57.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#define MAX_ENTRIES 42

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI random";
SDL_Surface * ecran = NULL;

const int trials = 10000000;
int essai = 0;
unsigned long counts[MAX_ENTRIES];

void draw_random() {
  
  char buffer[1024];
  int i;
  unsigned long max_count = 0;
  unsigned long sum_count = 0;
  for(i = 0; i < MAX_ENTRIES; ++i) {
    max_count = (max_count > counts[i]) ? max_count : counts[i];
    sum_count += counts[i];
  }
  for(i = 0; i < MAX_ENTRIES; ++i) {
    boxRGBA(ecran, 
      300, 100 + (i * (hauteur - 200)) / (MAX_ENTRIES + 1), 
      300 + ((largeur - 400) * (counts[i])) / max_count, 100 + ((i + 1) * (hauteur - 200)) / (MAX_ENTRIES + 1), 
      127, 127, 127, 255);
    rectangleRGBA(ecran, 
      300, 100 + (i * (hauteur - 200)) / (MAX_ENTRIES + 1), 
      300 + ((largeur - 400) * (counts[i])) / max_count, 100 + ((i + 1) * (hauteur - 200)) / (MAX_ENTRIES + 1), 
      255, 255, 255, 255);
    sprintf(buffer, "P(X = %d) = %g", i, (double)counts[i] / sum_count);
    stringRGBA(ecran, 10, 100 + ((i + 0.5) * (hauteur - 200)) / (MAX_ENTRIES + 1), buffer, 255, 255, 255, 255);
  }
  sprintf(buffer, "%d / %d essais", essai, trials);
  stringRGBA(ecran, 10, 10, buffer, 255, 255, 255, 255);
}

int uniform_random(int entries) {
  return rand() % entries;
}

int baised_fair_take_random(int entries) {
  int i;
  for(i = 0; i < entries; ++i) {
    if(rand() % entries == 0) return i;
  }
  return entries - 1;
}

int triangular_random(int entries) {
  int first = uniform_random(entries);
  int second = uniform_random(entries);
  return first < second ? first : second;
}

int exponential_random(int entries, const int roundness) {
  int i;
  for(;;) {
    for(i = 0; i < entries; ++i) {
      if(rand() % roundness == 0) return i;
    }
  }
}

int exponential_high_random(int entries) {
  return exponential_random(entries, 2);
}

int exponential_medium_random(int entries) {
  return exponential_random(entries, 3);
}

int exponential_low_random(int entries) {
  return exponential_random(entries, 10);
}

int normal_random(int entries) {
  const int splits = 4;
  int i;
  long sum = 0;
  for(i = 0; i < splits; ++i) {
    sum += uniform_random(entries);
  }
  return sum / splits;
}

int gamma_random(int entries) {
  const int splits = 2;
  int i;
  long sum = 0;
  for(i = 0; i < splits; ++i) {
    sum += triangular_random(entries);
  }
  return sum / splits;
}

int mix_uniform_normal_random(int entries, const double factor) {
  if(uniform_random(1000) / 1000. < factor) {
    return uniform_random(entries);
  }
  return normal_random(entries);
}

int mix_un_high_random(int entries) {
  return mix_uniform_normal_random(entries, 0.8);
}

int mix_un_medium_random(int entries) {
  return mix_uniform_normal_random(entries, 0.5);
}

int mix_un_low_random(int entries) {
  return mix_uniform_normal_random(entries, 0.2);
}

int troll_random(int entries) {
  const int splits = 3;
  int i;
  int val = 1;
  for(i = 0; i < splits; ++i) {
    val = (uniform_random(entries) * val) % entries;
  }
  if(val == 0) return troll_random(entries);
  return val;
}

void test_random(int entries, int (*random)(int)) {
  char buffer[1024];
  int i;
  for(i = 0; i < MAX_ENTRIES; ++i) {
    counts[i] = 0;
  }
  unsigned long t = 1;
  int updates = 0;
  for(essai = 0; essai < trials; ++essai) {
    ++(counts[random(entries)]);
    if(essai > t || essai % 10000 == 0) {
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
        draw_random();
      SDL_Flip(ecran);
      if(essai > t) {
        t *= 2;
        SDL_Delay(1 + 1000 / (++updates));
      }
    }
  }
}

int read_command() {
  printf("Aléatoires :\n");
  printf(" 1. uniform random\n");
  printf(" 2. baised fair take random\n");
  printf(" 3. triangular random\n");
  printf(" 4. exponential high random\n");
  printf(" 5. exponential medium random\n");
  printf(" 6. exponential low random\n");
  printf(" 7. normal random\n");
  printf(" 8. gamma random\n");
  printf(" 9. mixed high random\n");
  printf(" 10. mixed medium random\n");
  printf(" 11. mixed low random\n");
  printf(" 12. troll random\n");
  
  printf(" 0. quitter\n");
  printf(">>> ");
  int choix;
  scanf("%d", &choix);
  switch(choix) {
    case 0 : return 0;
    case 1 : test_random(MAX_ENTRIES, uniform_random); break;
    case 2 : test_random(MAX_ENTRIES, baised_fair_take_random); break;
    case 3 : test_random(MAX_ENTRIES, triangular_random); break;
    case 4 : test_random(MAX_ENTRIES, exponential_high_random); break;
    case 5 : test_random(MAX_ENTRIES, exponential_medium_random); break;
    case 6 : test_random(MAX_ENTRIES, exponential_low_random); break;
    case 7 : test_random(MAX_ENTRIES, normal_random); break;
    case 8 : test_random(MAX_ENTRIES, gamma_random); break;
    case 9 : test_random(MAX_ENTRIES, mix_un_high_random); break;
    case 10 : test_random(MAX_ENTRIES, mix_un_medium_random); break;
    case 11 : test_random(MAX_ENTRIES, mix_un_low_random); break;
    case 12 : test_random(MAX_ENTRIES, troll_random); break;
    
    default : break;
  }
  return 1;
}

int main() {
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Еrror in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Еrror in SDL_SetVideoMode : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(titre, NULL);
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
  SDL_Flip(ecran);
                                   
  while(read_command()) {
    
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 51));
    draw_random();
    SDL_Flip(ecran);
    SDL_Delay(1000 / 60);
  }
                                  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}