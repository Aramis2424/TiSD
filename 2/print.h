#ifndef PRINT_H
#define PRINT_H

#include "structures.h"

void print_all(students_t const arr[], int *len);
void print_part(students_t const arr[], int *len, int *year);
void print_all_k(students_t const arr[], int *len, keys_t arrk[]);
void print_menu();
void print_keys(keys_t arrk[], int *len);

#endif
