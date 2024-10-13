#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/db.h"
#include "../include/tree.h"

// Base de données sous forme d'arbre binaire
void db_init() {
    tree_init();
}

void db_insert(char *clé, char *valeur) {
    db_entry *entry = malloc(sizeof(db_entry));
    entry->clé = strdup(clé);
    entry->valeur = strdup(valeur);
    tree_insert(entry);
    
    // Afficher les données dans l'arbre après l'insertion
    printf("État actuel de l'arbre après l'insertion :\n");
    tree_print_in_order(tree_root);
}

char *db_select(char *clé) {
    db_entry *entry = tree_search(clé);
    return entry ? strdup(entry->valeur) : NULL; // Retourne une copie de la valeur
}

void db_modify(char *clé, char *nouvelle_valeur) {
    db_entry *entry = tree_search(clé);
    if (entry != NULL) {
        free(entry->valeur); // Libérer l'ancienne valeur
        entry->valeur = strdup(nouvelle_valeur); // Mettre la nouvelle valeur
    }
}

void db_delete(char *clé) {
    tree_delete(clé);
}

void db_init(const char *filename) {
    tree_init();
    db_load_from_disk(filename); // Charger les données à partir du disque
}


void db_close(const char *filename) {
    db_save_to_disk(filename);  // Sauvegarder les données avant de fermer
    tree_free();
}


void db_save_to_disk(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    if (tree_root == NULL) {
        printf("Aucune donnée à sauvegarder. L'arbre est vide.\n");
    } else {
        tree_save_in_order(tree_root, file);  // Sauvegarde de l'arbre dans le fichier
    }

    fflush(file);  // Force l'écriture dans le fichier
    fclose(file);
    printf("Sauvegarde terminée dans %s.\n", filename);
}



void db_load_entry(char *line) {
    // Enlever le retour à la ligne à la fin
    line[strcspn(line, "\n")] = 0;  // Supprimer le caractère de nouvelle ligne

    char *clé = strtok(line, ",");
    char *valeur = strtok(NULL, ",");
    if (clé && valeur) {
        db_insert(clé, valeur); // Insérer dans la base de données
    }
}



void db_load_from_disk(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        db_load_entry(line);  // Charger chaque entrée
    }

    fclose(file);
}
