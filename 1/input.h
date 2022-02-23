#ifndef INPUT
#define INPUT

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_MANTISSA_LEN (2 * MANTISSA_LEN)
#define MANTISSA_LEN 30
#define DEGREE_LEN 5

#define FALSE 0
#define TRUE 1

#define ERROR_WRONG_SYMBOL 2
#define EXIT_TOO_LONG_NUMBER 3
#define TOO_BIG_DEGREE 4

typedef struct
{
    char mantissa_sign;

    int mantissa_int[MAX_MANTISSA_LEN];
    int mantissa_int_len;
    int mantissa_float[MAX_MANTISSA_LEN];
    int mantissa_float_len;

    char degree_sign;

    int degree;
} real_t;

int real_scan(real_t *number);
void arr_print(int arr[], size_t len);
void real_print(real_t a);
int analysis_rc(int rc);

#endif
