#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "defines.h"
#include "errors.h"
#include "node.h"

int fill_matrix_man(matrix_t *matrix, spa_matrix_t *spa_matrix)
{
    int n, m;
    n = matrix->row;
    m = matrix->col;

    printf("Imput elements:\n");
    matrix->data = calloc(m * n, sizeof(double));
    spa_matrix->A = calloc(n * m, sizeof(double));
    spa_matrix->JA = calloc(n * m, sizeof(int));
    int count_non_null_elems = 0;
    double number;
    int k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (scanf("%lf", &number) != 1)
                return READING_ERROR;
            k = i * m + j;
            matrix->data[k] = number;
            if (number != 0)
            {
                spa_matrix->A[count_non_null_elems] = number;
                spa_matrix->JA[count_non_null_elems] = j;
                count_non_null_elems++;
            }
        }
        node_t *tmp = node_create(&count_non_null_elems);
        list_add_end(&spa_matrix->IA, tmp);
    }
    spa_matrix->A = realloc(spa_matrix->A, count_non_null_elems*sizeof(double));
    spa_matrix->JA = realloc(spa_matrix->JA, count_non_null_elems*sizeof(int));
    spa_matrix->size = count_non_null_elems;
    return TRUE;
}

int fill_matrix_auto(matrix_t *matrix, spa_matrix_t *spa_matrix)
{
    int n, m;
    n = matrix->row;
    m = matrix->col;
    FILE *f = fopen("matrix.txt", "r");
    if (!f)
        return ERROR_OPENING_FILE;

    matrix->col = m;
    matrix->row = n;
    matrix->data = calloc(n * m, sizeof(double));
    spa_matrix->A = calloc(n * m, sizeof(double));
    spa_matrix->JA = calloc(n * m, sizeof(int));
    int count_non_null_elems = 0;
    int number;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (fscanf(f, "%d", &number) == 1)
            {
                int k = i * m + j;
                matrix->data[k] = number;
                if (number != 0)
                {
                    spa_matrix->A[count_non_null_elems] = number;
                    spa_matrix->JA[count_non_null_elems] = j;
                    count_non_null_elems++;
                }
            }
            else
            {
                free(matrix->data);
                free(spa_matrix->A);
                free(spa_matrix->JA);
                fclose(f);
                return INVALID_ELEMENTS;
            }
        }
        node_t *tmp = node_create(&count_non_null_elems);
        list_add_end(&spa_matrix->IA, tmp);
    }
    if (fscanf(f, "%d", &number) == 1)
    {
        free(matrix->data);
        return INVALID_SIZE;
    }
    fclose(f);

    spa_matrix->A = realloc(spa_matrix->A, count_non_null_elems*sizeof(double));
    spa_matrix->JA = realloc(spa_matrix->JA, count_non_null_elems*sizeof(int));
    spa_matrix->size = count_non_null_elems;
    return TRUE;
}

int fill_vector_man(matrix_t *vector, spa_vector_t *spa_vector)
{
    int n = vector->row;
    vector->col = 1;

    printf("Input elements: \n");
    vector->data = calloc(n, sizeof(double));
    spa_vector->A = calloc(n, sizeof(double));
    spa_vector->JA = calloc(n, sizeof(int));
    int count_non_null_elems = 0;
    int number;
    for (int j = 0; j < n; j++)
    {
        if (scanf("%d", &number) != 1)
            return READING_ERROR;
        vector->data[j] = number;
        if (number != 0)
        {
            spa_vector->A[count_non_null_elems] = number;
            spa_vector->JA[count_non_null_elems] = j;
            count_non_null_elems++;
        }
    }
    spa_vector->A = realloc(spa_vector->A, count_non_null_elems*sizeof(double));
    spa_vector->JA = realloc(spa_vector->JA, count_non_null_elems*sizeof(int));
    spa_vector->size = count_non_null_elems;
    return TRUE;
}

int fill_vector_auto(matrix_t *vector, spa_vector_t *spa_vector)
{
    FILE *f = fopen("vector.txt", "r");
    if (!f)
        return ERROR_OPENING_FILE;

    int n = vector->row;
    vector->col = 1;
    vector->data = calloc(n, sizeof(double));
    int count_non_null_elems = 0;
    spa_vector->A = calloc(n, sizeof(double));
    spa_vector->JA = calloc(n, sizeof(int));
    int number;
    for (int i = 0; i < n; i++)
    {
        if (fscanf(f, "%d", &number) == 1)
            vector->data[i] = number;
        else
        {
            free(vector->data);
            fclose(f);
            return ERROR_READING_FILE;
        }
        if (number != 0)
        {
            spa_vector->A[count_non_null_elems] = number;
            spa_vector->JA[count_non_null_elems] = i;
            count_non_null_elems++;
        }
    }
    if (fscanf(f, "%d", &number) == 1)
    {
        free(vector->data);
        return INVALID_SIZE;
    }
    spa_vector->A = realloc(spa_vector->A, count_non_null_elems*sizeof(double));
    spa_vector->JA = realloc(spa_vector->JA, count_non_null_elems*sizeof(int));
    spa_vector->size = count_non_null_elems;
    fclose(f);
    return TRUE;
}
