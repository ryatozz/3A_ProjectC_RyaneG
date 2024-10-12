#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"

void ajouter_entree();
void modifier_entree();
void supprimer_entree();
void afficher_entree();

int main() {
    db_init();

    int choix;

    do {
        printf("Menu:\n");
        printf("1. Ajouter une entrée\n");
        printf("2. Modifier une entrée\n");
        printf("3. Supprimer une entrée\n");
        printf("4. Afficher une entrée\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        getchar(); // Consomme le '\n' restant

        switch (choix) {
            case 1:
                ajouter_entree();
                break;
            case 2:
                modifier_entree();
                break;
            case 3:
                supprimer_entree();
                break;
            case 4:
                afficher_entree();
                break;
            case 5:
                printf("Fermeture de la base de données.\n");
                db_close();
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);

    return 0;
}

void ajouter_entree() {
    char clé[100];
    char valeur[100];

    printf("Entrez la clé: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    printf("Entrez la valeur: ");
    fgets(valeur, sizeof(valeur), stdin);
    valeur[strcspn(valeur, "\n")] = 0;

    db_insert(clé, valeur);
    printf("Entrée ajoutée avec succès.\n");
}

void modifier_entree() {
    char clé[100];
    char nouvelle_valeur[100];

    printf("Entrez la clé à modifier: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    printf("Entrez la nouvelle valeur: ");
    fgets(nouvelle_valeur, sizeof(nouvelle_valeur), stdin);
    nouvelle_valeur[strcspn(nouvelle_valeur, "\n")] = 0;

    db_modify(clé, nouvelle_valeur);
    printf("Entrée modifiée avec succès.\n");
}

void supprimer_entree() {
    char clé[100];

    printf("Entrez la clé à supprimer: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    db_delete(clé);
    printf("Entrée supprimée avec succès.\n");
}

void afficher_entree() {
    char clé[100];
    printf("Entrez la clé à afficher: ");
    fgets(clé, sizeof(clé), stdin);
    clé[strcspn(clé, "\n")] = 0;

    char *valeur = db_select(clé);
    if (valeur) {
        printf("Valeur : %s\n", valeur);
        free(valeur); // Libérer la mémoire
    } else {
        printf("Aucune entrée trouvée pour la clé : %s\n", clé);
    }
}