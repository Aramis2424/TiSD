#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mult.h"
#include "print.h"

#define EPS 1e-8

int matrix_mult(matrix_t *matrix, matrix_t *vector, matrix_t *res)
{
    if (matrix->col != vector->row)
    {
        printf("Mult is impossible!\n");
        printf("Count of collumns in matrix should be equal len of vector\n");
        return FALSE;
    }

    res->col = 1;
    res->row = matrix->row;
    res->data = calloc(matrix->row, sizeof(double));

    int k = 0;
    for (int i = 0; i < matrix->row; i++)
    {
        res->data[i] = 0;
        for (int j = 0; j < vector->row; j++)
        {
            res->data[i] += (vector->data[j] *
                               matrix->data[k * matrix->col + j]);
        }
        k++;
    }
    return TRUE;
}

void spa_matrix_mult(spa_matrix_t *matrix,spa_vector_t *vector,spa_vector_t *res)
{
    res->A = calloc(matrix->size + vector->size, sizeof(double));
    res->JA = calloc(matrix->size + vector->size, sizeof(int));
    int count_elems = 0;

    int end = matrix->IA.Nk;
    node_t *tmp = matrix->IA.next;
    int start = 0;
    int row = 0;
    int index_row = 0;
    while (start != matrix->size)
    {
        start = end;
        if (start == matrix->size)
            break;
        end = tmp->Nk;
        tmp = tmp->next;
        for (int i = start; i < end; i++) //идем по строке
        {
            int index_col = matrix->JA[i];
            index_row = 0;
            while (vector->JA[index_row] != index_col)
            {
                index_row++;
                if (index_row > vector->size)
                {
                    index_row = -1;
                    break;
                }
            }
            if (index_row == -1)
                continue;
            double tmp = matrix->A[i] * vector->A[index_row];
            res->A[count_elems] += tmp;
        }
        if (fabs(res->A[count_elems]) > EPS)
        {
            res->JA[count_elems] = row;
            count_elems++;
        }
        row++;
    }
    res->size = count_elems;
    res->A = realloc(res->A, count_elems * sizeof(double));
    res->JA = realloc(res->JA, count_elems * sizeof(int));
}
