#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>
#include "print.h"
#include "functions.h"
#include "structures.h"
#include "defines.h"
#include "read.h"
#include "mult.h"
#include "errors.h"

#define MAX_MENU_CODE 11
#define MIN_MENU_CODE 0

#define STR_LEN 10
#define OUTPUT_SIZE 5

int main(void)
{
    matrix_t vector = { 0, 0, NULL };
    spa_vector_t spa_vector = { 0, 0, 0 };
    matrix_t matrix = { 0, 0, NULL };
    spa_matrix_t spa_matrix = { 0, 0, 0, { 0, 0 } };
    matrix_t res = { 0, 0, NULL };
    spa_vector_t spa_res = { 0, 0, 0 };
    srand(time(NULL)); //Для генерации случайных чисел
    print_intro();
    printf("Input size of matrix:\n");
    printf(" rows: ");
    if (scanf("%d", &matrix.row) != 1 || matrix.row == 0)
    {
        printf("Invalid input\n");
        printf("Size should be a positive integer\n");
        return INPUT_ERROR;
    }
    printf(" columns: ");
    if (scanf("%d", &matrix.col) != 1 || matrix.col == 0)
    {
        printf("Invalid input\n");
        printf("Size should be a positive integer\n");
        return INPUT_ERROR;
    }
    printf("\nInput size of vector: ");
    if (scanf("%d", &vector.row) != 1 || vector.row == 0)
    {
        printf("Invalid input\n");
        printf("Size should be a positive integer\n");
        return INPUT_ERROR;
    }
    printf("\n");

    if (matrix.col != vector.row)
    {
        printf("Sorry but multiplication is not possible\n");
        printf("The number of columns of the matrix ");
        printf("must be equal to the size of the vector\n");
        return INVALID_SIZE;
    }

    //ввод матрицыs
    int choice;
    printf("Enter 1, if you want fill matrix manually\n");
    printf("Enter 2, if you want fill matrix from file\n");
    printf("Enter 3, if you want fill matrix by random numbers\n");
    printf("Enter 4, if you want fill matrix using coordinates\n");
    if (scanf("%d", &choice)!=1 || (choice > 4 || choice < 1))
    {
        printf("Invalid input\n");
        printf("Your choice should be 1 or 2 or 3 or 4\n");
        return INPUT_ERROR;
    }
    int rc;
    if (choice == 1)
    {
        rc = fill_matrix_man(&matrix, &spa_matrix);
        if (rc != TRUE)
        {
            printf("Sorry, but input is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }
    if (choice == 2)
    {
        rc = fill_matrix_auto(&matrix, &spa_matrix);
        if (rc == INVALID_SIZE)
        {
            printf("Sorry, but matrix size is wrang\n");
            printf("Try again\n");
            return INVALID_SIZE;
        }
        if (rc != TRUE)
        {
            printf("Sorry, but file is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }
    if (choice == 3)
    {
        printf("Imput percentage of matrix filling (0%%..100%%): ");
        int percent;
        if (scanf("%d", &percent) != 1 || percent < 0 || percent > 100)
        {
            printf("Invalid input\n");
            printf("Percent is positive integer\n");
            return INPUT_ERROR;
        }
        random_fill_matrix(&matrix, percent, &spa_matrix);
        printf("If you want to see your matrix, enter 1, else enter 0\n");
        if (scanf("%d", &choice)!=1 || (choice != 1 && choice != 0))
        {
            printf("Invalid input\n");
            printf("Your choice should be 1 or 0\n");
            return INPUT_ERROR;
        }
        if (choice == 1)
        {
            printf("Your matrix is: \n");
            if (matrix.row <= OUTPUT_SIZE && matrix.col <= OUTPUT_SIZE)
                print_matrix(&matrix);
            else
                print_spa_matrix(&spa_matrix);
        }
    }
    if (choice == 4)
    {
        int non_null;
        printf("Enter count of non-null elements (less then: %d): \n", matrix.col*matrix.row);
        if (scanf("%d", &non_null) != 1 || non_null > matrix.col * matrix.row)
        {
            printf("Invalid input\n");
            return INPUT_ERROR;
        }
        rc = fill_matrix_coord(&matrix, non_null, &spa_matrix);
        if (rc != TRUE)
        {
            printf("Sorry, but input is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }

    //ввод вектора
    printf("Enter 1, if you want fill vector manually\n");
    printf("Enter 2, if you want fill vector from file\n");
    printf("Enter 3, if you want fill vector by random numbers\n");
    printf("Enter 4, if you want fill vector using coordinates\n");
    if (scanf("%d", &choice)!=1 || (choice > 4 || choice < 1))
    {
        printf("Invalid input\n");
        printf("Your choice should be 1 or 2 or 3 or 4\n");
        return INPUT_ERROR;
    }
    if (choice == 1)
    {
        rc = fill_vector_man(&vector, &spa_vector);
        if (rc != TRUE)
        {
            printf("Sorry, but input is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }
    if (choice == 2)
    {
        rc = fill_vector_auto(&vector, &spa_vector);
        if (rc == INVALID_SIZE)
        {
            printf("Sorry, but vector size is wrang\n");
            printf("Try again\n");
            return INVALID_SIZE;
        }
        if (rc != TRUE)
        {
            printf("Sorry, but file is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }
    if (choice == 3)
    {
        printf("Imput percentage of vector filling (0%%..100%%): ");
        int percent;
        if (scanf("%d", &percent) != 1 || percent < 0 || percent > 100)
        {
            printf("Invalid input\n");
            printf("Percent is positive integer\n");
            return INPUT_ERROR;
        }
        random_fill_vector(&vector, percent, &spa_vector);
        printf("If you want to see your vector, enter 1, else enter 0\n");
        if (scanf("%d", &choice)!=1 || (choice != 1 && choice != 0))
        {
            printf("Invalid input\n");
            printf("Your choice should be 1 or 0\n");
            return INPUT_ERROR;
        }
        if (choice == 1)
        {
            printf("Your vector is: \n");
            if (vector.row <= OUTPUT_SIZE)
                print_vector(&vector);
            else
                print_spa_vector(&spa_vector);
        }
    }
    if (choice == 4)
    {
        int non_null;
        printf("Enter count of non-null elements (less then: %d): \n", vector.row);
        if (scanf("%d", &non_null) != 1 || non_null > vector.row)
        {
            printf("Invalid input\n");
            return INPUT_ERROR;
        }
        rc = fill_vector_coord(&vector, non_null, &spa_vector);
        if (rc != TRUE)
        {
            printf("Sorry, but input is wrang\n\n");
            return INPUT_ERROR;
        }
        printf("Command complete\n");
    }

    //умножение
    printf("\nThe result of mult is:\n");
    if (spa_matrix.size == 0 || spa_vector.size == 0)
    {
        printf("Null matrix %dx%d\n", matrix.col, 1);
        return EXIT_SUCCESS;
    }
    if (matrix.row <= OUTPUT_SIZE)
    {
        rc = matrix_mult(&matrix, &vector, &res);
        print_matrix(&res);
    }
    else
    {
        spa_matrix_mult(&spa_matrix, &spa_vector, &spa_res);
        print_spa_vector(&spa_res);
    }

    printf("\nCompare:\n");
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;
    int count_rep = 1000;
    for (int i = 0; i < count_rep; i++)
    {
        gettimeofday(&tv_start, NULL);
        matrix_mult(&matrix, &vector, &res);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);
    }
    elapsed_time /= count_rep;

    printf("Classical mult: \n");
    printf(" *time: %" PRId64 " us\n", elapsed_time);
    int memory = sizeof(double)*(matrix.col * matrix.row + vector.row);
    printf(" *memory: %d bytes\n", memory);
    count_rep = 10000;
    for (int i = 0; i < count_rep; i++)
    {
        gettimeofday(&tv_start, NULL);
        spa_matrix_mult(&spa_matrix, &spa_vector, &spa_res);
        gettimeofday(&tv_stop, NULL);
        elapsed_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);
    }
    elapsed_time /= count_rep;
    printf("Sparse mult: \n");
    printf(" -time: %" PRId64 " us\n", elapsed_time);
    memory = sizeof(double)*(spa_vector.size) + sizeof(int)*(spa_vector.size);
    memory += (sizeof(double)*(spa_matrix.size) + sizeof(int)*(spa_matrix.size));
    memory += sizeof(node_t)*(matrix.row);
    //память под вектор: память на элементы + память на индексы столбцов
    printf(" *memory: %d bytes\n", memory);

    free(matrix.data);
    free(vector.data);
    free(res.data);
    printf("End program\n");
    return EXIT_SUCCESS;
}
