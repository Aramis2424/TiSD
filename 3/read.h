#ifndef READ_H
#define READ_H

#include "structures.h"

int fill_matrix_auto(matrix_t *matrix, spa_matrix_t *spa_matrix);
int fill_vector_auto(matrix_t *vector, spa_vector_t *spa_vector);
int fill_matrix_man(matrix_t *matrix, spa_matrix_t *spa_matrix);
int fill_vector_man(matrix_t *matrix, spa_vector_t *spa_vector);

#endif
