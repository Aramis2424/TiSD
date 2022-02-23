#ifndef HASH_H
#define HASH_H

#define MAX_COLL 500

typedef struct cell_t cell_t ;
struct cell_t
{
    int number;
    int id;
    cell_t *next;
};

typedef struct
{
    cell_t *data;
    int coll;
    int now_count_elem;
    int count_elem;
}table_t;

void freetable(table_t *table);
table_t *create_table(int n);
table_t* fill_table(table_t *table, int key);
int search_hash(table_t **table, int key, int *count, int max_count);

#endif
