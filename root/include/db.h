// db.h
#ifndef DB_H
#define DB_H

typedef struct {
    char *clé;
    char *valeur;
} db_entry;

void db_init();
void db_insert(char *clé, char *valeur);
char *db_select(char *clé);
void db_delete(char *clé); // Ajoutez cette ligne
void db_modify(char *clé, char *nouvelle_valeur);
void db_close();

#endif
