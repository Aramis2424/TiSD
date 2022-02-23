#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

int is_integer(const char *str);
void random_fill_matrix(matrix_t *matrix, int percent, spa_matrix_t *spa_matrix);
void random_fill_vector(matrix_t *vector, int percent, spa_vector_t *spa_vector);
int fill_matrix_coord(matrix_t *matrix, int non_null, spa_matrix_t *spa_matrix);
int fill_vector_coord(matrix_t *vector, int non_null, spa_vector_t *spa_vector);

#endif
