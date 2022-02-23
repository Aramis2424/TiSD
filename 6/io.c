#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "io.h"
#include "defines.h"
#include "errors.h"
#include "hash.h"
#include "functions.h"

void print_intro(void)
{
    printf("Hello!\n");
    printf("This program builds trees and hash tables\n");
    printf("from integer numbers.\n");
    printf("The program also performs standard\n");
    printf("operations with trees and hash tables.\n");
    printf("------------------------------------------\n");
    printf("\n");
}

void print_menu(void)
{
    printf("Menu:\n");
    printf("   1)Read data from file;\n");
    printf("   2)Print trees and table;\n");
    printf("   3)Add number;\n");
    printf("   4)Element search;\n");
    //printf("   5);\n");
    printf("   0)Exit.\n");
    printf("----------\n");
}

int scan_tree(tree_node **head, int *count)
{
    FILE *f = fopen(FILE_NAME, "r");
    if (!f)
        return ERROR_OPENING_FILE;
    int number;

    while (fscanf(f, "%d", &number) == 1)
    {
        (*count)++;
        tree_node *node = tree_node_create(number);
        if (!node)
            return ALLOCATED_ERROR;
        node->height = 1;
        *head = tree_node_add(*head, node);
    }

    fclose(f);
    return OK;
}

int scan_tree_bal(tree_node **head, int *count)
{
    FILE *f = fopen(FILE_NAME, "r");
    if (!f)
        return ERROR_OPENING_FILE;
    int number;

    while (fscanf(f, "%d", &number) == 1)
    {
        (*count)++;
        tree_node *node = tree_node_create(number);
        if (!node)
            return ALLOCATED_ERROR;
        node->height = 1;
        *head = tree_bal_node_add(*head, node);
    }

    fclose(f);
    balance_tree(*head);
    return OK;
}

void scan_table(FILE *f, table_t **table)
{
    int count = 0;
    int number;
    while (fscanf(f, "%d", &number) == 1)
        count++;
    count = next_prime(count);
    rewind(f);

    table_t *tab = create_table(count);
    while (fscanf(f, "%d", &number) == 1)
        tab = fill_table(tab, number);
    *table = tab;
}

void print_table(table_t *table)
{
    printf("Hash table:\n");
    printf("\nCollisions: %d\n", table->coll);
    printf("|   i   |   Hash   |   Number   |\n");
    printf("=================================\n");
    cell_t *tmp = NULL;

    int num_index = 0;
    for (int i = 0; i < table->count_elem; i++)
    {
        int flag = 0;
        tmp = &table->data[i];
        while (tmp && tmp->id != 0)
        {
            int hash = abs(table->data[i].number) % table->count_elem;
            int num = tmp->number;
            printf("| %3d   |   %4d   |   %6d   |\n", num_index, hash, num);
            tmp = tmp->next;
            flag++;
            num++;
        }
        if (flag == 0)
            printf("| %3d   |   ----   |   ------   |\n", num_index);
        num_index++;
    }
    printf("\n");
}
