#include <stdio.h>
#include "print.h"

void print_intro(void)
{
    printf("The program multiplies the matrix by a column vector\n");
    printf("You can enter the matrix in three ways:\n");
    printf(" 1)Manually\n");
    printf(" 2)From the file\n");
    printf(" 3)Create a matrix of random numbers\n");
    printf(" 4)By coordinates\n");
    printf("The size of the matrix are integers\n");
    printf("Matrix elements are double numbers\n");
    printf("To multiply, the number of columns of the matrix ");
    printf("must be equal to the number of rows of the vector\n");
    printf("\n");
}

void print_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->row; i++)
    {
        for (int j = 0; j < matrix->col; j++)
        {
            int k = i * matrix->col + j;
            printf("%.3lf   ", matrix->data[k]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(matrix_t *vector)
{
    for (int i = 0; i < vector->row; i++)
        printf("%.3lf\n", vector->data[i]);
    printf("\n");
}

void print_spa_vector(spa_vector_t *spa_vector)
{
    printf("Row:   Value:\n");
    for (int i = 0; i < spa_vector->size; i++)
    {
        printf(" %d     " ,spa_vector->JA[i]);
        printf("%.3lf\n" ,spa_vector->A[i]);
    }
}

void print_spa_matrix(spa_matrix_t *spa_matrix)
{
    printf("Row:   Column:   Value:\n");
    int end = spa_matrix->IA.Nk;
    node_t *tmp = spa_matrix->IA.next;
    int start = 0;
    int row = 0;
    while (start != spa_matrix->size)
    {
        start = end;
        if (start != spa_matrix->size)
        {
            end = tmp->Nk;
            tmp = tmp->next;
        }
        for (int i = start; i < end; i++)
        {
            printf(" %d     " , row);
            printf(" %d     " ,spa_matrix->JA[i]);
            printf("%.3lf\n" ,spa_matrix->A[i]);
        }
        row++;
    }
}
