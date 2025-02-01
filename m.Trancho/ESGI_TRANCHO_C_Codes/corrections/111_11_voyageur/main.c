/**
 * ESGI : Cours de Langage C de Kevin TRANCHO.
 * Correction de l'exercice 111.
 */

/*
Résultats attendus :
star sous 1s : sous 1500
star sous 10s : sous 1000

rectangle sous 1s : sous 4000

city sous 20s : sous 9000
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

/* Paramètres de la fenêtre : */
const int largeur = 800;
const int hauteur = 600;
const char * titre = "ESGI delivery";

#define SELECT 10
#define GENERATE 1000

typedef struct Point Point;
struct Point {
  int x;
  int y;
};

double Point_distance(const Point * first, const Point * second) {
  return sqrt((first->x - second->x) * (first->x - second->x) + (first->y - second->y) * (first->y - second->y));
}

/* Modélisation de la liste utilisateur : une liste de points. */
/* Pour permettre un ajout dynamique, nous gardons le nombre   */
/* de valeurs affectées et la capacité de l'allocation. */
Point * userInput = NULL;
int taille = 0;
int capacite = 0;

/* Modélisation d'une solution : correspondance avec liste     */
/* utilisateur par indices et sauvegarde de la distance de la  */
/* solution. */
typedef struct Entry Entry;
struct Entry {
  int * indexes;
  double distance;
};

int generations = 0;
Entry * currentEntry = NULL;
Entry * entries = NULL;
clock_t start;

/* Initialisation d'une solution sur la liste utilisateur : */
Entry Entry_toPositions(Point * points, int taille) {
  Entry ent;
  if((ent.indexes = (int *)calloc(taille, sizeof(int))) == NULL) {
    fprintf(stderr, "Erreur d\'allocation d\'une entrée.\n");
    exit(EXIT_FAILURE);
  }
  ent.distance = 0.;
  int i;
  for(i = 0; i < taille; ++i) {
    if(i) {
      ent.distance += Point_distance(points + i, points + i - 1);
    }
    ent.indexes[i] = i;
  }
  return ent;
}

/* Initialisation de la population de solutions : */
void Entries_init() {
  if((entries = (Entry *)calloc(GENERATE, sizeof(Entry))) == NULL) {
    fprintf(stderr, "Erreur d\'allocation de %d entrées (entrées).\n", GENERATE);
    exit(EXIT_FAILURE);
  }
  int i;
  for(i = 0; i < GENERATE; ++i) {
    entries[i] = Entry_toPositions(userInput, taille);
  }
  currentEntry = entries;
}

/* Calcul de la distance pour une solution donnée : */
void Entry_compute_distance(Entry * ent) {
  ent->distance = 0.;
  int i;
  for(i = 1; i < taille; ++i) {
    ent->distance += Point_distance(userInput + ent->indexes[i], userInput + ent->indexes[i - 1]);
  }
}

/* Échange de l'ordre deux positions dans une solution : */
void Entries_swap(int i, int j) {
  if(i == j) {
    return;
  }
  int k;
  for(k = 0; k < taille; ++k) {
    entries[i].indexes[k] ^= entries[j].indexes[k];
    entries[j].indexes[k] ^= entries[i].indexes[k];
    entries[i].indexes[k] ^= entries[j].indexes[k];
  }
  double d = entries[i].distance;
  entries[i].distance = entries[j].distance;
  entries[j].distance = d;
}

void Entries_copy(int dest, int src) {
  int k;
  for(k = 0; k < taille; ++k) {
    entries[dest].indexes[k] = entries[src].indexes[k];
  }
  entries[dest].distance = entries[src].distance;
}

/* Mutation : plusieurs échanges sur solution actuelle */
void Entry_evolve_lot_of_swaps(Entry * ent) {
  int psize = rand() % (taille);
  int k;
  for(k = 0; k < psize; ++k) {
    int i;
    int j;
    i = rand() % taille;
    j = rand() % taille;
    if(i == j)
      return;
    ent->indexes[i] ^= ent->indexes[j];
    ent->indexes[j] ^= ent->indexes[i];
    ent->indexes[i] ^= ent->indexes[j];
  }
}

/* Mutation : plusieurs échanges depuis départ */
void Entry_evolve_reset_lot_of_swaps(Entry * ent) {
  int psize = rand() % (taille);
  int step = rand() % (taille);
  int k, l, i = 0;
  for(l = 0; l < step; ++l) {
    for(k = l; k < taille; k += step) {
      ent->indexes[k] = i++;
    }
  }
  for(k = 0; k < psize; ++k) {
    int i;
    int j;
    i = rand() % taille;
    j = rand() % taille;
    if(i == j)
      return;
    ent->indexes[i] ^= ent->indexes[j];
    ent->indexes[j] ^= ent->indexes[i];
    ent->indexes[i] ^= ent->indexes[j];
  }
}

/* Mutation : un seul échange */
void Entry_evolve_unique(Entry * ent) {
  int i;
  int j;
  i = rand() % taille;
  j = rand() % taille;
  if(i == j)
    return;
  ent->indexes[i] ^= ent->indexes[j];
  ent->indexes[j] ^= ent->indexes[i];
  ent->indexes[i] ^= ent->indexes[j];
}

/* Mutation : recherche d'une plus petite distance pour échange */
void Entry_evolve_win_one(Entry * ent) {
  int i;
  int j;
  int psize = rand() % (taille);
  i = rand() % taille;
  j = (i + 1) % taille;
  int k, l;
  for(k = 0; k < psize; ++k) {
    l = rand() % taille;
    if(l == i)  
      continue;
    if(Point_distance(userInput + i, userInput + l) < Point_distance(userInput + i, userInput + j)) {
      j = l;
    }
  }
  if(i == j)
    return;
  ent->indexes[i] ^= ent->indexes[j];
  ent->indexes[j] ^= ent->indexes[i];
  ent->indexes[i] ^= ent->indexes[j];
}

/* Mutation : pivot sur un sous-chemin */
void Entry_evolve_propag(Entry * ent) {
  int i, a, b;
  int psize = rand() % (taille / 2);
  i = rand() % taille;
  int k;
  for(k = 0; k < psize; ++k) {
    a = (i + k) % taille;
    b = (i + 1 + k) % taille;
    ent->indexes[a] ^= ent->indexes[b];
    ent->indexes[b] ^= ent->indexes[a];
    ent->indexes[a] ^= ent->indexes[b];
  }
}

/* Mutation : répétition de recherches minimales */
void Entry_evolve_lot_of_win_one(Entry * ent) {
  int psize = rand() % (taille);
  int k;
  for(k = 0; k < psize; ++k) {
    Entry_evolve_win_one(ent);
  }
}

/* Mutation : tentative de construction d'une chemin minimal */
void Entry_evolve_try_chain(Entry * ent) {
  int i;
  int j;
  int k;
  int l;
  int m;
  i = rand() % taille;
  j = rand() % taille;
  for(k = i; k != j; k = (k + 1) % taille) {
    m = 1;
    for(l = 2; l < taille; ++l) {
      if(Point_distance(userInput + k, userInput + ((k + l) % taille)) < Point_distance(userInput + k, userInput + ((k + m) % taille))) {
        m = l;
      }
    }
    if(m != 1) {
      ent->indexes[((k + 1) % taille)] ^= ent->indexes[((k + m) % taille)];
      ent->indexes[((k + m) % taille)] ^= ent->indexes[((k + 1) % taille)];
      ent->indexes[((k + 1) % taille)] ^= ent->indexes[((k + m) % taille)];
    }
  }
}

/* Mutation : permutation de plusieurs positions */
void Entry_evolve_perm(Entry * ent) {
  int perm[20];
  int psize;
  if(taille < 20) {
    psize = rand() % taille;
  } else {
    psize = rand() % 20;
  }
  if(psize <= 1) {
    return;
  }
  int i;
  for(i = 0; i < psize; ++i) {
    perm[i] = rand() % taille;
  }
  for(i = 1; i < psize; ++i) {
    int a = perm[i], b = perm[0];
    if(a == b)
      continue;
    ent->indexes[a] ^= ent->indexes[b];
    ent->indexes[b] ^= ent->indexes[a];
    ent->indexes[a] ^= ent->indexes[b];
  }
}

/* Mutation : rotation de tout le chemin */
void Entry_evolve_rotation(Entry * ent) {
  int i;
  for(i = 0; i < taille - 1; ++i) {
    ent->indexes[i] ^= ent->indexes[i + 1];
    ent->indexes[i + 1] ^= ent->indexes[i];
    ent->indexes[i] ^= ent->indexes[i + 1];
  }
}

/* Mutation : rotations de tout le chemin */
void Entry_evolve_rotations(Entry * ent) {
  int i = rand() % taille;
  for(; i > 0; --i) {
    Entry_evolve_rotation(ent);
  }
}

/* Mutation : mélange aléatoire */
void Entry_evolve_shuffle(Entry * ent) {
  int i, j;
  for(i = 0; i < taille; ++i) {
    ent->indexes[i] = -1;
  }
  for(i = 0; i < taille; ++i) {
    for(j = rand() % taille; ent->indexes[j] >= 0; j = (j + 1) % taille)
      ;
    ent->indexes[j] = i;
  }
}

/* Mutation d'une solution */
void Entry_evolve(Entry * ent) {
  int choix = 1;
  /* Selection des fonctions de mutation selon l'avancement : */
  if(generations > 5000 && taille < 100) {
    choix = 10;
  } else if(generations > 2000 && taille < 100) {
    choix = 6;
  } else if(generations > 1000 && taille < 100) {
    choix = 4;
  } else if(generations > 600) {
    choix = 3;
  } else if(generations > 300) {
    choix = 2;
  }
  /* Mélanger aléatoirement la liste utilisateur au début : */
  if(generations < taille / 10) {
    Entry_evolve_shuffle(ent);
    return;
  }
  /* Application de la mutation : */
  switch(rand() % choix) {
    case 0 :
      Entry_evolve_unique(ent);
      break;
      
    case 1 :
      Entry_evolve_propag(ent);
      break;
      
    case 2 :
      Entry_evolve_perm(ent);
      break;
      
    case 3 :
      Entry_evolve_rotations(ent);
      break;
      
    case 4 :
      Entry_evolve_win_one(ent);
      break;
      
    case 5 :
      Entry_evolve_try_chain(ent);
      break;
      
    case 6 :
      Entry_evolve_reset_lot_of_swaps(ent);
      break;
      
    case 7 :
      Entry_evolve_lot_of_win_one(ent);
      break;
      
    case 8 :
      Entry_evolve_lot_of_swaps(ent);
      break;
      
    case 9 :
      Entry_evolve_shuffle(ent);
      break;
  }
  /* Pour une génération avancée, combiner des mutations : */
  if(generations > 500) {
    int mv = (generations > 5000) ? 5000 : generations;
    if(rand() % mv > 500) {
      Entry_evolve(ent);
    }
  }
}

/* Duplique et mute dans la population une des meilleures solutions */
void Entries_duplicate_best() {
  int i;
  for(i = SELECT; i < GENERATE; ++i) {
    Entries_copy(i, i % SELECT);
    Entry_evolve(entries + i);
    Entry_compute_distance(entries + i);
  }
}

void Entries_update() {
  /* Dupliquer et muter les meilleures solutions : */
  Entries_duplicate_best();
  int i, j;
  /* Pour les solutions ayant muté : */
  for(i = SELECT; i < GENERATE; ++i) {
    /* Si la solution bat la plus faible de la selection : */
    if(entries[i].distance < entries[SELECT - 1].distance) {
      /* La faire remonter tant qu'elle bat les solutions : */
      for(j = SELECT - 1; j >= 0; --j) {
        if(entries[j].distance < entries[i].distance) {
          break;
        }
      }
      ++j;
      Entries_swap(i, j);
    }
  }
  currentEntry = entries;
  ++generations;
}

/* Mise à jour de la capacité de la liste utilisateur : */
void updateInput() {
  if(taille >= capacite) {
    capacite = taille * 2 + 10;
    if((userInput = (Point *)realloc(userInput, sizeof(Point) * capacite)) == NULL) {
      fprintf(stderr, "Erreur d\'allocation de l\'entrée utilisateur.\n");
      exit(EXIT_FAILURE);
    }
  }
}

/* Ajout d'un point par l'utilisateur : */
void addInput(int x, int y) {
  updateInput();
  userInput[taille].x = x;
  userInput[taille].y = y;
  ++taille;
}

void affichage(SDL_Surface * ecran) {
  /* Remplissage de l'écran par un gris foncé uniforme : */
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 51, 51, 102));
  
  int i;
  double distance = 0.;
  /* Dessin de la liste : */
  if(currentEntry == NULL) {
    /* Telle que saisie (avant optimisation) : */
    for(i = 0; i < taille; ++i) {
      if(i) {
        lineRGBA(ecran, userInput[i - 1].x, userInput[i - 1].y, userInput[i].x, userInput[i].y, 204, 204, 204, 255);
        distance += Point_distance(userInput + i, userInput + i - 1);
      }
      filledCircleRGBA(ecran, userInput[i].x, userInput[i].y, 3, 204, 204, 204, 255);
    }
  } else {
    /* Meilleures solution : */
    for(i = 0; i < taille; ++i) {
      filledCircleRGBA(ecran, userInput[i].x, userInput[i].y, 3, 204, 204, 204, 255);
    }
    for(i = 1; i < taille; ++i) {
      lineRGBA(ecran, userInput[currentEntry->indexes[i]].x, userInput[currentEntry->indexes[i]].y, userInput[currentEntry->indexes[i - 1]].x, userInput[currentEntry->indexes[i - 1]].y, 204, 204, 0, 255);
    }
    distance = currentEntry->distance;
  }
  char buffer[512];
  sprintf(buffer, "%d positions", taille);
  stringRGBA(ecran, 5, 5, buffer, 255, 255, 255, 255);
  if(currentEntry == NULL) {
    sprintf(buffer, "Distance totale : %g", distance);
  } else {
    sprintf(buffer, "Generation %d (%g s)", generations, (double)(clock() - start) / CLOCKS_PER_SEC);
  }
  stringRGBA(ecran, 5, 25, buffer, 255, 255, 255, 255);
  if(entries != NULL) {
    for(i = 0; i < SELECT; ++i) {
      sprintf(buffer, "Solution %d : %g", i + 1, entries[i].distance);
      stringRGBA(ecran, 5, 45 + i * 20, buffer, 255, 255, 255, 255);
    }
  }
}

int Points_save(const char * path, const Point * points, int size) {
  FILE * file = NULL;
  if((file = fopen(path, "w+")) == NULL) {
    fprintf(stderr, "Erreur ouverture %s\n", path);
    return 0;
  }
  int i;
  fprintf(file, "%d\n", size);
  for(i = 0; i < size; ++i) {
    fprintf(file, "%d %d\n", points[i].x, points[i].y);
  }
  fclose(file);
  return 1;
}

int Points_load(const char * path, Point ** points, int * size) {
  FILE * file = NULL;
  if((file = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Erreur ouverture %s\n", path);
    return 0;
  }
  int i;
  fscanf(file, "%d", size);
  if((*points = (Point *)calloc(*size, sizeof(Point))) == NULL) {
    fprintf(stderr, "Erreur allocation %s\n", path);
    fclose(file);
    return 0;
  }
  for(i = 0; i < *size; ++i) {
    fscanf(file, "%d %d", &((*points)[i].x), &((*points)[i].y));
  }
  fclose(file);
  return 1;
}

int main(int argc, char * argv[]) {
  srand(time(NULL));
  /* Création d'une fenêtre SDL : */
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Surface * ecran = NULL;
  if((ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption(titre, NULL);
  
  if(argc > 1) {
    Points_load(argv[1], &userInput, &taille);
    capacite = taille;
  }
  
  int active = 1;
  int optimise = 0;
  SDL_Event event;
  
  while(active) {
    
    affichage(ecran);
    SDL_Flip(ecran);
    
    while(SDL_PollEvent(&event)) {
      
      switch(event.type) {
        /* Utilisateur clique sur la croix de la fenêtre : */
        case SDL_QUIT : {
          active = 0;
        } break;
        
        /* Utilisateur enfonce une touche du clavier : */
        case SDL_KEYDOWN : {
          switch(event.key.keysym.sym) {
            /* Touche Echap : */
            case SDLK_ESCAPE : {
              active = 0;
            } break;
            
            default : break;
          }
        } break;
        
        case SDL_KEYUP : {
          switch(event.key.keysym.sym) {
            case SDLK_SPACE : {
              if(! optimise) {
                Entries_init();
                start = clock();
              }
              optimise = 1;
            } break;
            
            case SDLK_s : {
              if(Points_save("save.points", userInput, taille)) {
                printf("Sauvegarde des points dans \"save.points\"\n");
              }
            } break;
            
            default : break;
          }
        } break;
        
        case SDL_MOUSEBUTTONUP : {
          switch(event.button.button) {
            case SDL_BUTTON_LEFT : {
              if(! optimise) {
                addInput(event.button.x, event.button.y);
              }
            } break;
            
            default : break;
          }
        } break;
        
        default : break;
      }
    }
    if(optimise) {
      Entries_update();
      SDL_Delay(1);
    } else {
      SDL_Delay(1000 / 60);
    }
    
  }
  
  SDL_FreeSurface(ecran);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}