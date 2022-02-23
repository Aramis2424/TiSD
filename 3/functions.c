#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "defines.h"
#include "functions.h"
#include "node.h"

int is_integer(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return FALSE;
    return TRUE;
}

void random_fill_matrix(matrix_t *matrix, int percent, spa_matrix_t *spa_matrix)
{
    int n = matrix->row;
    int m = matrix->col;
    matrix->data = calloc(n*m, sizeof(double));

    double tmp = percent * n * m / 100.0;
    int count_non_null_elems = rint(tmp);
    spa_matrix->size = count_non_null_elems;
    spa_matrix->A = calloc(count_non_null_elems, sizeof(double));
    spa_matrix->JA = calloc(count_non_null_elems, sizeof(int));
    int rand_i, rand_j;
    for (int b = 0; b < count_non_null_elems; b++)
    {
        do //что бы случайные индексы не повторялись
        {
            rand_i = rand() % n;
            rand_j = rand() % m;
        }
        while (matrix->data[rand_i * m + rand_j] != 0);
        int rand_number = (rand() % 5) + 1;
        matrix->data[rand_i * m + rand_j] = rand_number;
    }
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int g = i * m + j;
            if (matrix->data[g] != 0)
            {
                spa_matrix->A[k] = matrix->data[g];
                spa_matrix->JA[k] = j;
                k++;
            }
        }
        node_t *tmp = node_create(&k);
        list_add_end(&spa_matrix->IA, tmp);
    }
}

void random_fill_vector(matrix_t *vector, int percent, spa_vector_t *spa_vector)
{
    int n = vector->row;
    vector->data = calloc(n, sizeof(double));

    double tmp = n * percent / 100.0;
    int count_non_null_elems = rint(tmp);

    spa_vector->size = count_non_null_elems;
    spa_vector->A = calloc(count_non_null_elems, sizeof(double));
    spa_vector->JA = calloc(count_non_null_elems, sizeof(int));
    int rand_j;
    for (int b = 0; b < count_non_null_elems; b++)
    {
        do //что бы случайные индексы не повторялись
            rand_j = rand() % n;
        while (vector->data[rand_j] != 0);

        int rand_number = (rand() % 5) + 1;
        vector->data[rand_j] = rand_number;
    }
    int i = 0;
    for (int j = 0; j < n; j++)
        if (vector->data[j] != 0)
        {
            spa_vector->A[i] = vector->data[j];
            spa_vector->JA[i] = j;
            i++;
        }
}

int fill_matrix_coord(matrix_t *matrix, int non_null, spa_matrix_t *spa_matrix)
{
    int n = matrix->row;
    int m = matrix->col;
    matrix->data = calloc(n*m, sizeof(double));

    spa_matrix->size = non_null;
    spa_matrix->A = calloc(non_null, sizeof(double));
    spa_matrix->JA = calloc(non_null, sizeof(int));
    int i, j, number;
    for (int b = 0; b < non_null; b++)
    {
        printf("Row (less then %d): ", n - 1);
        if (scanf("%d", &i) != 1 || i > n - 1)
        {
            printf("Invalid input\n");
            return FALSE;
        }
        printf("Column (less then %d): ", m - 1);
        if (scanf("%d", &j) != 1 || j > m - 1)
        {
            printf("Invalid input\n");
            return FALSE;
        }
        printf("Number: ");
        if (scanf("%d", &number) != 1)
        {
            printf("Invalid input\n");
            return FALSE;
        }
        matrix->data[i * m + j] = number;
    }
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int g = i * m + j;
            if (matrix->data[g] != 0)
            {
                spa_matrix->A[k] = matrix->data[g];
                spa_matrix->JA[k] = j;
                k++;
            }
        }
        node_t *tmp = node_create(&k);
        list_add_end(&spa_matrix->IA, tmp);
    }
    return TRUE;
}

int fill_vector_coord(matrix_t *vector, int non_null, spa_vector_t *spa_vector)
{
    int n = vector->row;
    vector->data = calloc(n, sizeof(double));

    spa_vector->size = non_null;
    spa_vector->A = calloc(non_null, sizeof(double));
    spa_vector->JA = calloc(non_null, sizeof(int));
    int i, number;
    for (int b = 0; b < non_null; b++)
    {
        printf("Row (less then %d): ", n - 1);
        if (scanf("%d", &i) != 1 || i > n - 1)
        {
            printf("Invalid input\n");
            return FALSE;
        }
        printf("Number: ");
        if (scanf("%d", &number) != 1)
        {
            printf("Invalid input\n");
            return FALSE;
        }
        vector->data[i] = number;
    }
    int k = 0;
    for (int j = 0; j < n; j++)
        if (vector->data[j] != 0)
        {
            spa_vector->A[k] = vector->data[j];
            spa_vector->JA[k] = j;
            k++;
        }
    return TRUE;
}
