#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "defines.h"
#include "errors.h"
#include "processing.h"

void print_intro(void);
void print_menu(void);

int scan_graph(char *str, int matrix[][MAX_N], node_t arrb[], int *len);
void print_graph(FILE *stream, int matr[][MAX_N], int n, int path[], int path_len);
void print_stdout_graph(node_t arrb[], int len);

#endif
