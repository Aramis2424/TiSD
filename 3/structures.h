#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_COL 2000
#define MAX_ROW 2000
#define MAX_ELEMS 4000000


//структура стандартной матрицы
typedef struct
{
    int col;
    int row;
    double *data;
} matrix_t;

typedef struct node_t node_t;
struct node_t
{
    int Nk;
    node_t *next;
};

//матрица в разреженном виде
typedef struct
{
    int size;
    double *A;
    int *JA;
    node_t IA;
}spa_matrix_t;

//разреженный вектор
typedef struct
{
    int size;
    double *A;
    int *JA;
}spa_vector_t;

#endif
