#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

tree_node *tree_root = NULL; // Déclaration globale

// Fonction pour initialiser l'arbre binaire
void tree_init() {
    tree_root = NULL;
}

// Fonction pour insérer une entrée dans l'arbre binaire
void tree_insert(db_entry *entry) {
    tree_node *node = malloc(sizeof(tree_node));
    node->entry = entry;
    node->gauche = NULL;
    node->droite = NULL;

    if (tree_root == NULL) {
        tree_root = node;
    } else {
        tree_insert_node(tree_root, node);
    }
}

// Fonction pour insérer un nœud dans l'arbre binaire
void tree_insert_node(tree_node *node, tree_node *new_node) {
    if (strcmp(new_node->entry->clé, node->entry->clé) < 0) {
        if (node->gauche == NULL) {
            node->gauche = new_node;
        } else {
            tree_insert_node(node->gauche, new_node);
        }
    } else {
        if (node->droite == NULL) {
            node->droite = new_node;
        } else {
            tree_insert_node(node->droite, new_node);
        }
    }
}

// Fonction pour rechercher une entrée dans l'arbre binaire
db_entry *tree_search(char *clé) {
    return tree_search_node(tree_root, clé);
}

// Fonction pour rechercher un nœud dans l'arbre binaire
db_entry *tree_search_node(tree_node *node, char *clé) {
    if (node == NULL) {
        return NULL;
    } else if (strcmp(clé, node->entry->clé) == 0) {
        return node->entry;
    } else if (strcmp(clé, node->entry->clé) < 0) {
        return tree_search_node(node->gauche, clé);
    } else {
        return tree_search_node(node->droite, clé);
    }
}

// Fonction pour libérer la mémoire allouée pour l'arbre binaire
void tree_free() {
    tree_free_node(tree_root);  // Libération de la mémoire à partir de la racine
    tree_root = NULL;            // Réinitialiser la racine
}

// Fonction pour libérer la mémoire allouée pour un nœud
void tree_free_node(tree_node *node) {
    if (node != NULL) {
        if (node->gauche != NULL) {
            tree_free_node(node->gauche);
        }
        if (node->droite != NULL) {
            tree_free_node(node->droite);
        }
        free(node->entry->clé);
        free(node->entry->valeur);
        free(node->entry);
        free(node);
    }
}

// Fonction pour supprimer une entrée de l'arbre binaire
void tree_delete(char *clé) {
    tree_root = tree_delete_node(tree_root, clé);
}

// Fonction pour supprimer un nœud dans l'arbre binaire
tree_node *tree_delete_node(tree_node *node, char *clé) {
    if (node == NULL) {
        return NULL; // La clé n'existe pas
    }

    // Trouver le nœud à supprimer
    if (strcmp(clé, node->entry->clé) < 0) {
        node->gauche = tree_delete_node(node->gauche, clé);
    } else if (strcmp(clé, node->entry->clé) > 0) {
        node->droite = tree_delete_node(node->droite, clé);
    } else {
        // Nœud trouvé
        if (node->gauche == NULL) {
            tree_node *temp = node->droite;
            free(node->entry->clé);
            free(node->entry->valeur);
            free(node->entry);
            free(node);
            return temp;
        } else if (node->droite == NULL) {
            tree_node *temp = node->gauche;
            free(node->entry->clé);
            free(node->entry->valeur);
            free(node->entry);
            free(node);
            return temp;
        }

        // Trouver le successeur (le plus petit dans le sous-arbre droit)
        tree_node *successeur = node->droite;
        while (successeur && successeur->gauche != NULL) {
            successeur = successeur->gauche;
        }

        // Remplacer les valeurs de `node` par celles de `successeur`
        free(node->entry->clé);
        free(node->entry->valeur);
        node->entry->clé = strdup(successeur->entry->clé);
        node->entry->valeur = strdup(successeur->entry->valeur);

        // Supprimer le successeur
        node->droite = tree_delete_node(node->droite, successeur->entry->clé);
    }

    return node;
}

void tree_save_in_order(tree_node *node, FILE *file) {
    if (node == NULL) {
        return;
    }

    tree_save_in_order(node->gauche, file);  // Parcourir le sous-arbre gauche
    fprintf(file, "%s,%s\n", node->entry->clé, node->entry->valeur);  // Écrire clé,valeur dans le fichier
    tree_save_in_order(node->droite, file);  // Parcourir le sous-arbre droit
}



// Fonction pour charger une entrée clé-valeur à partir d'une ligne de fichier
void tree_load_entry(char *line) {
    char *clé = strtok(line, "=");
    char *valeur = strtok(NULL, "\n");
    if (clé != NULL && valeur != NULL) {
        db_entry *entry = malloc(sizeof(db_entry));
        entry->clé = strdup(clé);
        entry->valeur = strdup(valeur);
        tree_insert(entry);  // Insère l'entrée dans l'arbre
        db_save_to_disk("database.txt");
    }
}

void tree_print_in_order(tree_node *node) {
    if (node == NULL) {
        return;
    }

    tree_print_in_order(node->gauche);  // Parcourir le sous-arbre gauche
    printf("Clé: %s, Valeur: %s\n", node->entry->clé, node->entry->valeur);  // Afficher la clé-valeur
    tree_print_in_order(node->droite);  // Parcourir le sous-arbre droit
}
