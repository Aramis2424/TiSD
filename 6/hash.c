#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "functions.h"
#include "errors.h"
#include "defines.h"
#include "io.h"

cell_t *creat_table_data(int n)
{
    cell_t *cell = calloc(n, sizeof(cell_t));
    return cell;
}

table_t *create_table(int n)
{
    table_t *table = malloc(sizeof(table_t));
    if (n == 1)
        n = 3;
    table->count_elem = n;

    table->data = calloc(n, sizeof(cell_t));

    table->coll = 0;
    table->now_count_elem = 0;

    return table;
}

void free_table(table_t *tab)
{
    free(tab->data);
    free(tab);
}

int hash_func(int key, int len)
{
    return (int)abs(key) % len;
}

table_t* restruct(table_t* old)
{
    table_t *new = create_table(old->count_elem);
    new->count_elem = old->count_elem;

    int old_count_elem = prev_prime(new->count_elem);

    cell_t *tmp_old = NULL;
    for (int i = 0; i < old_count_elem; i++)
    {
        tmp_old = &old->data[i];
        while (tmp_old && tmp_old->id != 0)
        {
            new = fill_table(new, tmp_old->number);
            tmp_old = tmp_old->next;
        }
    }

    return new;
}

table_t* fill_table(table_t *table, int key)
{
    if (table == NULL)
        return NULL;
    table->now_count_elem++;
    if (table->now_count_elem >= table->count_elem)
    {
        table->count_elem = next_prime(table->count_elem);
        table = restruct(table);
        table->now_count_elem++;
    }

    int tmp_id = 1;
    int h = hash_func(key, table->count_elem);
    cell_t *tmp = &table->data[h];
    while (tmp->next != NULL)
    {
        if (tmp->number == key)
            return table;
        tmp_id++;

        if (table->coll >= MAX_COLL)
        {
            table->now_count_elem++;
            table->count_elem = next_prime(table->count_elem);
            table = restruct(table);
            table->now_count_elem++;
            h = hash_func(key, table->count_elem);
            tmp = &table->data[h];
            continue;
        }
        tmp = tmp->next;
    }

    if (tmp_id != 1)
    {
        cell_t *new_temp = calloc(1, sizeof(cell_t));
        cell_t *new = calloc(1, sizeof(cell_t));
        new->id = tmp_id;
        new->next = new_temp;
        new->number = key;
        *tmp = *new;

        table->coll++;
    }
    else
    {
        cell_t *new_temp = calloc(1, sizeof(cell_t));
        tmp->id = 1;
        tmp->next = new_temp;
        tmp->number = key;
    }

    return table;
}

int search_hash(table_t **table, int key, int *count, int max_count)
{
    int place = hash_func(key, (*table)->count_elem);
    cell_t *tmp = NULL;

    tmp = &(*table)->data[place];
    while (tmp && tmp->id != 0)
    {
        (*count)++;
        if (*count > max_count)// && max_count != 1)
        {
            *count = 0;
            (*table)->count_elem = next_prime((*table)->count_elem);



            (*table)->now_count_elem++;

            *table = restruct(*table);


            (*table)->now_count_elem++;
            return search_hash(table, key, count, max_count);
        }
        if (tmp->number == key)
            return place;
        tmp = tmp->next;
    }

    return -1;
}
