#include "normalization.h"

int ctoi(const char symbol)
{
    return symbol - '0';
}

int last_elem(int arr[], int *len, int *transfer)
{
    *transfer = arr[(*len) - 1];
    (*len)--;
    return TRUE;
}

int insert(int arr[], int len, int element)
{
    for (int i = len - 1; i >= 0; i--)
        arr[i + 1] = arr[i];
    arr[0] = element;
    return TRUE;
}

int shift_arr(int arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
        arr[i] = arr[i + 1];
    return TRUE;
}

void del_insignificant_zeros(real_t *number)
{
    while (number->mantissa_int[0] == 0)
    {
        if (number->mantissa_int_len <= 1)
            break;
        shift_arr(number->mantissa_int, number->mantissa_int_len);
        number->mantissa_int_len--;
    }

    int len = number->mantissa_float_len;
    while (number->mantissa_float[len - 1] == 0)
    {
        if (len == 1)
            break;
        len--;
    }
    number->mantissa_float_len = len;
}

void add_insignificant_zeros(real_t *n_1, real_t *n_2)
{
    int len_n_1 = n_1->mantissa_float_len;
    int len_n_2 = n_2->mantissa_float_len;

    while (len_n_1 > len_n_2)
    {
        len_n_2++;
        n_2->mantissa_float[len_n_2] = 0;
    }
    n_2->mantissa_float_len = len_n_2;
}

void define_sign(real_t *number, int new_number)
{
    if (number->degree_sign == '-')
        number->degree *= -1;
    number->degree += new_number;
    if (number->degree < 0)
    {
        number->degree_sign = '-';
        number->degree *= -1;
    }
    else
        number->degree_sign = '+';
}

void round_up(real_t *number, int *new_degree)
{
    int transfer;
    if (number->mantissa_float_len == 1 && number->mantissa_float[0] == 0)
        number->mantissa_float_len--;
    number->mantissa_float_len += number->mantissa_int_len;
    while (number->mantissa_int_len > 0)
    {
        last_elem(number->mantissa_int, &(number->mantissa_int_len), &transfer);
        insert(number->mantissa_float, number->mantissa_float_len, transfer);
        (*new_degree)++;
    }
    number->mantissa_int[0] = 0;
    number->mantissa_int_len++;
}

void round_down(real_t *number, int *new_degree)
{
    while (number->mantissa_float[0] == 0)
    {
        if (number->mantissa_float_len <= 1)
            break;
        shift_arr(number->mantissa_float, number->mantissa_float_len);
        number->mantissa_float[number->mantissa_float_len - 1] = 0;
        number->mantissa_float_len--;
        (*new_degree)--;
    }
}

void res_round(real_t *number)
{
    int transfer = 0;
    int n = 1;
    if (number->mantissa_float_len > MANTISSA_LEN)
    {
        if (number->mantissa_float[MANTISSA_LEN] >= 5)
        {
            number->mantissa_float[MANTISSA_LEN - n]++;
            while (number->mantissa_float[MANTISSA_LEN - n] > 9)
            {
                transfer = number->mantissa_float[MANTISSA_LEN - n] / 10;
                number->mantissa_float[MANTISSA_LEN - n] %= 10;
                n++;
                number->mantissa_float[MANTISSA_LEN - n] += transfer;
                if (n == MANTISSA_LEN)
                {
                    if (number->mantissa_float[0] > 9)
                    {
                        number->mantissa_float[0] = 1;
                        number->degree++;
                    }
                    break;
                }
            }
        }
        number->mantissa_float_len = MANTISSA_LEN;
    }
}

int normalization(real_t *number)
{
    int new_degree = 0;

    if (number->mantissa_int[0] != 0)
    {
        round_up(number, &new_degree);
        define_sign(number, new_degree);
        return TRUE;
    }

    //Попадаем только если int_arr[0] == 0
    if (number->mantissa_float[0] == 0)
    {
        round_down(number, &new_degree);
        define_sign(number, new_degree);
        return TRUE;
    }

    return TRUE;
}
