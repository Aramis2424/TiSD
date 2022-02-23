#ifndef NORMALIZATION
#define NORMALIZATION

#include "input.h"

int ctoi(const char symbol);
int last_elem(int arr[], int *len, int *transfer);
int insert(int arr[], int len, int element);
int shift_arr(int arr[], int len);
void del_insignificant_zeros(real_t *number);
void add_insignificant_zeros(real_t *n_1, real_t *n_2);
void define_sign(real_t *number, int new_number);
void round_up(real_t *number, int *new_degree);
void round_down(real_t *number, int *new_degree);
int normalization(real_t *number);
void res_round(real_t *number);

#endif
