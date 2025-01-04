#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void listFiles(const char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);

    if (dr == NULL) {
        printf("Could not open directory %s\n", path);
        return;
    }

    printf("\nContents of %s:\n", path);
    printf("----------------------------\n");
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);

    closedir(dr);
}

int main() {
    int choice;
    char path[256];
    char filename[100];

     if (getcwd(path, sizeof(path)) == NULL) {
        printf("Error getting the current working directory");
        return EXIT_FAILURE;
    }

    while (1) {
        printf("Current directory: %s\n", path);
        printf("===================================\n");
        printf("| 1 - View files                   |\n");
        printf("| 2 - Change directory             |\n");
        printf("| 3 - Create file                  |\n");
        printf("| 4 - Delete file                  |\n");
        printf("| 5 - Exit                         |\n");
        printf("===================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Ignorer Entrée

        switch (choice) {
            case 1:
                listFiles(path);
                break;

            case 2:
                printf("\nEnter the path to change directory: ");
                fgets(path, sizeof(path), stdin);
                path[strcspn(path, "\n")] = 0; // Ignorer \n
                if (chdir(path) == 0) {
                    printf("Changed to directory %s\n", path);
                    getcwd(path, sizeof(path));// Mettre a jour le chemin
                } else {
                    printf("Could not change directory to %s\n", path);
                }
                break;

            case 3:
                printf("\nEnter the name of the file to create: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // Ignorer \n
                FILE *fp = fopen(filename, "w");
                if (fp) {
                    printf("File created successfully\n");
                    fclose(fp);
                } else {
                    printf("Could not create the file %s\n", filename);
                }
                break;

            case 4:
                printf("\nEnter the name of the file to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // Ignorer \n
                if (remove(filename) == 0) {
                    printf("File deleted successfully\n");
                } else {
                    printf("Could not delete the file %s\n", filename);
                }
                break;

            case 5:
                printf("\nExiting..\n");
                exit(0);

            default:
                printf("\nInvalid choice, please try again.\n");
        }
    }

    return EXIT_SUCCESS;
}
