#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_NUMBER_LENGTH 15

// Structure pour stocker une entrée dans le carnet d'adresses
typedef struct {
    char name[MAX_NAME_LENGTH];
    char number[MAX_NUMBER_LENGTH];
} Entry;

// Fonction pour charger les données à partir d'un fichier
int load_file(const char *file_name, Entry **phonebook, int *size) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        return 0; // Fichier inexistant ou erreur d'ouverture
    }

    *size = 0;
    // Lire les lignes du fichier et les ajouter dans le tableau
    while (!feof(file)) {
        *phonebook = realloc(*phonebook, (*size + 1) * sizeof(Entry));
        fscanf(file, "%99s %14s\n", (*phonebook)[*size].name, (*phonebook)[*size].number);
        (*size)++;
    }

    fclose(file);
    return 1;
}

// Fonction pour enregistrer les données dans un fichier
void save_file(const char *file_name, Entry *phonebook, int size) {
    FILE *file = fopen(file_name, "w");
    if (!file) {
        printf("Erreur d'ouverture du fichier pour l'enregistrement\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %s\n", phonebook[i].name, phonebook[i].number);
    }

    fclose(file);
}

// Fonction pour ajouter une nouvelle entrée
void add_entry(Entry **phonebook, int *size) {
    *phonebook = realloc(*phonebook, (*size + 1) * sizeof(Entry));
    printf("Entrez le nom: ");
    scanf("%s", (*phonebook)[*size].name);
    printf("Entrez le numéro: ");
    scanf("%s", (*phonebook)[*size].number);
    (*size)++;
}

// Fonction pour rechercher un numéro par nom
void search_number(Entry *phonebook, int size) {
    char name[MAX_NAME_LENGTH];
    printf("Entrez le nom à rechercher: ");
    scanf("%s", name);

    for (int i = 0; i < size; i++) {
        if (strcmp(phonebook[i].name, name) == 0) {
            printf("Numéro de téléphone de %s: %s\n", name, phonebook[i].number);
            return;
        }
    }
    printf("Nom non trouvé.\n");
}

int main(int argc, char *argv[]) {
    Entry *phonebook = NULL;
    int size = 0;
    char file_name[MAX_NAME_LENGTH] = "";

    // Analyse des arguments
    if (argc < 2) {
        printf("Usage: %s -i [fichier d'entrée] -o [fichier de sortie]\n", argv[0]);
        return 1;
    }

    // Gestion des options -i et -o
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            strcpy(file_name, argv[i + 1]);
            if (!load_file(file_name, &phonebook, &size)) {
                printf("Aucun fichier trouvé ou erreur de lecture\n");
            }
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            strcpy(file_name, argv[i + 1]);
        }
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Ajouter une entrée\n");
        printf("2. Rechercher un numéro\n");
        printf("3. Sauvegarder dans le fichier\n");
        printf("4. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_entry(&phonebook, &size);
                break;
            case 2:
                search_number(phonebook, size);
                break;
            case 3:
                save_file(file_name, phonebook, size);
                printf("Données sauvegardées dans %s\n", file_name);
                break;
            case 4:
                printf("Quitter le programme\n");
                break;
            default:
                printf("Choix invalide, essayez de nouveau\n");
        }
    } while (choice != 4);

    // Libérer la mémoire utilisée par le carnet d'adresses
    free(phonebook);

    return 0;
}
