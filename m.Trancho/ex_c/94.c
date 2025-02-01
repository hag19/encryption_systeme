#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM_LENGTH 50

// Structure to store a name and its associated number
typedef struct Node {
    char nom[MAX_NOM_LENGTH];
    char numero[MAX_NOM_LENGTH];
    struct Node* next;  // Pointer to the next node
} Node;

// Function to create a new node
Node* createNode(char* nom, char* numero) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->nom, nom);
    strcpy(newNode->numero, numero);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertNode(Node** head, char* nom, char* numero) {
    Node* newNode = createNode(nom, numero);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to search for a name in the list
Node* searchNode(Node* head, char* recherche) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->nom, recherche) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
Node* searchNodeNumero(Node* head, char* recherche) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->numero, recherche) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
// Function to free the memory of the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;  // Head of the linked list
    int n, i;
    char nom[MAX_NOM_LENGTH], numero[MAX_NOM_LENGTH], recherche[MAX_NOM_LENGTH];
    
    // Ask the user how many names they want to enter
    printf("Combien de noms souhaitez-vous entrer ? \n");
    scanf("%d", &n);
    getchar();  // Consume the leftover newline character from scanf
    
    // Ask the user to input names and their associated numbers
    for (i = 0; i < n; i++) {
        printf("Entrez le nom #%d\n: ", i + 1);
        scanf("%49s", nom);  // Use scanf with %49s to avoid buffer overflow
        if(searchNode(head, nom) != NULL) {
            printf("Le nom %s existe déjà. Entrez un autre nom.\n", nom);
            i--;
            continue;
        }
        printf("Entrez le numéro associé à %s\n: ", nom);
        scanf("%49s", numero);  // Use scanf with %49s to avoid buffer overflow
        if(searchNodeNumero(head, numero) != NULL) {
            printf("Le numéro %s existe déjà. Entrez un autre numéro.\n", numero);
            i--;
            continue;
        }
        insertNode(&head, nom, numero);
    }

    // Ask the user to search for a name
    printf("Entrez un nom à rechercher: \n");
    scanf("%49s", recherche);  // Use scanf with %49s to avoid buffer overflow

    // Search for the name in the linked list
    Node* result = searchNode(head, recherche);
    if (result != NULL) {
        printf("Le numéro associé à %s est %s.\n", result->nom, result->numero);
    } else {
        printf("Le nom %s n'a pas été trouvé.\n", recherche);
    }

    // Free the linked list memory
    freeList(head);

    return 0;
}
