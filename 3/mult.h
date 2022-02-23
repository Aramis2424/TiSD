#ifndef MULT_H
#define MULT_H

#include "structures.h"
#include "defines.h"

int matrix_mult(matrix_t *matrix, matrix_t *vector, matrix_t *res);
void spa_matrix_mult(spa_matrix_t *matrix,spa_vector_t *vector,spa_vector_t *res);

#endif
