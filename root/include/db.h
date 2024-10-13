// db.h
#ifndef DB_H
#define DB_H

typedef struct {
    char *clé;
    char *valeur;
} db_entry;

// Structure pour une ligne dans une table (représentée ici par un tableau de db_entry)
typedef struct {
    db_entry *entries;  // Tableau d'entrées (clé-valeur)
    int num_entries;    // Nombre d'entrées dans la ligne
} db_row;

// Structure pour une table (ici, un tableau de lignes)
typedef struct {
    db_row *rows;       // Tableau de lignes
    int num_rows;       // Nombre de lignes
} db_table;

void db_init();
void db_insert(char *clé, char *valeur);
char *db_select(char *clé);
void db_delete(char *clé);
void db_modify(char *clé, char *nouvelle_valeur);
void db_close();

// Fonctions pour la persistance sur disque
void db_save_to_disk(const char *filename);
void db_load_from_disk(const char *filename);

#endif
