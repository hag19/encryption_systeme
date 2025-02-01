#include <stdio.h>

#define MAX_VIE 100
#define MAX_ATTAQUE 50
#define MAX_DEFENSE 20
#define MAX_VITESSE 100

// Define enums for stats and spells
typedef enum { VIE, ATTAQUE, DEFENSE, VITESSE } Stat;
typedef enum { COUP, REDUIRE_ATTAQUE, REDUIRE_DEFENSE, REDUIRE_VITESSE, SOIN, AUGMENT_ATTAQUE, AUGMENT_DEFENSE, AUGMENT_VITESSE } Sort;

// Stats structure for the characters
typedef struct {
    int vie;
    int attaque;
    int defense;
    int vitesse;
} Stats;

// Character structure
typedef struct {
    char nom[50];
    Stats stats;
    Stats stats_actuelles;  // Current stats (modified by spells)
} Personnage;

// Function to display the stats of a character
void afficher_stats(Personnage p) {
    printf("Vie: %d | Attaque: %d | Defense: %d | Vitesse: %d\n",
            p.stats_actuelles.vie, p.stats_actuelles.attaque, p.stats_actuelles.defense, p.stats_actuelles.vitesse);
}

// Function to apply a spell
void appliquer_sort(Personnage *attaquant, Personnage *defenseur, Sort sort) {
    switch (sort) {
        case COUP:
            // Coup deals damage based on the attacker's attack and defender's defense
            if (defenseur->stats_actuelles.vie > 0) {
                int degats = attaquant->stats_actuelles.attaque - defenseur->stats_actuelles.defense;
                if (degats < 0) degats = 0;  // Ensure damage cannot be negative
                defenseur->stats_actuelles.vie -= degats;
                printf("%s inflicts %d damage to %s\n", attaquant->nom, degats, defenseur->nom);
            }
            break;
        case REDUIRE_ATTAQUE:
            // Reduces the attack of the defender
            defenseur->stats_actuelles.attaque -= 10;
            if (defenseur->stats_actuelles.attaque < 0) defenseur->stats_actuelles.attaque = 0;
            printf("%s reduces the attack of %s by 10\n", attaquant->nom, defenseur->nom);
            break;
        case REDUIRE_DEFENSE:
            // Reduces the defense of the defender
            defenseur->stats_actuelles.defense -= 5;
            if (defenseur->stats_actuelles.defense < 0) defenseur->stats_actuelles.defense = 0;
            printf("%s reduces the defense of %s by 5\n", attaquant->nom, defenseur->nom);
            break;
        case REDUIRE_VITESSE:
            // Reduces the speed of the defender
            defenseur->stats_actuelles.vitesse -= 10;
            if (defenseur->stats_actuelles.vitesse < 0) defenseur->stats_actuelles.vitesse = 0;
            printf("%s reduces the speed of %s by 10\n", attaquant->nom, defenseur->nom);
            break;
        case SOIN:
            // Heals the attacker
            attaquant->stats_actuelles.vie += 20;
            if (attaquant->stats_actuelles.vie > attaquant->stats.vie) attaquant->stats_actuelles.vie = attaquant->stats.vie;
            printf("%s heals themselves for 20 points\n", attaquant->nom);
            break;
        case AUGMENT_ATTAQUE:
            // Increases the attack of the attacker
            attaquant->stats_actuelles.attaque += 10;
            if (attaquant->stats_actuelles.attaque > MAX_ATTAQUE) attaquant->stats_actuelles.attaque = MAX_ATTAQUE;
            printf("%s increases their attack by 10\n", attaquant->nom);
            break;
        case AUGMENT_DEFENSE:
            // Increases the defense of the attacker
            attaquant->stats_actuelles.defense += 5;
            if (attaquant->stats_actuelles.defense > MAX_DEFENSE) attaquant->stats_actuelles.defense = MAX_DEFENSE;
            printf("%s increases their defense by 5\n", attaquant->nom);
            break;
        case AUGMENT_VITESSE:
            // Increases the speed of the attacker
            attaquant->stats_actuelles.vitesse += 10;
            if (attaquant->stats_actuelles.vitesse > MAX_VITESSE) attaquant->stats_actuelles.vitesse = MAX_VITESSE;
            printf("%s increases their speed by 10\n", attaquant->nom);
            break;
    }
}

// Combat function
void combat(Personnage *p1, Personnage *p2) {
    int tour = 1;
    while (p1->stats_actuelles.vie > 0 && p2->stats_actuelles.vie > 0) {
        printf("\nTurn %d\n", tour);
        afficher_stats(*p1);
        afficher_stats(*p2);

        int choix;
        Personnage *attaquant = (tour % 2 == 1) ? p1 : p2;
        Personnage *defenseur = (tour % 2 == 1) ? p2 : p1;

        printf("\n%s, choose a spell:\n", attaquant->nom);
        printf("1. Attack\n2. Reduce Attack\n3. Reduce Defense\n4. Reduce Speed\n5. Heal\n6. Increase Attack\n7. Increase Defense\n8. Increase Speed\n");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 8) {
            appliquer_sort(attaquant, defenseur, (Sort)(choix - 1));
        } else {
            printf("Invalid choice, you lose this turn.\n");
        }

        tour++;
    }

    // Display the final result
    if (p1->stats_actuelles.vie <= 0) {
        printf("%s lost, %s wins!\n", p1->nom, p2->nom);
    } else {
        printf("%s lost, %s wins!\n", p2->nom, p1->nom);
    }
}

int main() {
    Personnage joueur = {"Player", {MAX_VIE, MAX_ATTAQUE, MAX_DEFENSE, MAX_VITESSE}, {MAX_VIE, MAX_ATTAQUE, MAX_DEFENSE, MAX_VITESSE}};
    Personnage adversaire = {"Adversary", {MAX_VIE, MAX_ATTAQUE, MAX_DEFENSE, MAX_VITESSE}, {MAX_VIE, MAX_ATTAQUE, MAX_DEFENSE, MAX_VITESSE}};

    combat(&joueur, &adversaire);

    return 0;
}