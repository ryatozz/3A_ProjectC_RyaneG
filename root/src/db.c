#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/db.h"
#include "../include/tree.h"

// Fonction pour initialiser la base de données
void db_init() {
    tree_init();
}

void db_insert(char *clé, char *valeur) {
    db_entry *entry = malloc(sizeof(db_entry));
    entry->clé = strdup(clé);
    entry->valeur = strdup(valeur);
    tree_insert(entry);
}

char *db_select(char *clé) {
    db_entry *entry = tree_search(clé);
    return entry ? strdup(entry->valeur) : NULL; // Return a copy of the value
}

void db_modify(char *clé, char *nouvelle_valeur) {
    db_entry *entry = tree_search(clé);
    if (entry != NULL) {
        free(entry->valeur); // Libérer l'ancienne valeur
        entry->valeur = strdup(nouvelle_valeur); // Affecter la nouvelle valeur
    }
}

void db_delete(char *clé) {
    // Implémenter la suppression
    tree_delete(clé);
}

void db_close() {
    tree_free();
}
