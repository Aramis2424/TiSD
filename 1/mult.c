#include <math.h>
#include "mult.h"
#include "normalization.h"

int is_zero(real_t *a)
{
    for (int i = 0; i < a->mantissa_float_len; i++)
        if (a->mantissa_float[i] != 0)
            return FALSE;
    return TRUE;
}

int real_mult(real_t *a, real_t *b, real_t *res)
{
    //Знак мантиссы
    if (a->mantissa_sign == b->mantissa_sign)
        res->mantissa_sign = '+';
    else
        res->mantissa_sign = '-';

    //Знак порядка
    res->degree = a->degree;
    res->degree_sign = a->degree_sign;
    if (b->degree_sign == '-')
        b->degree *= -1;
    define_sign(res, b->degree);

    //Выравнивание длины мантисс
    if (a->mantissa_float_len > b->mantissa_float_len)
        add_insignificant_zeros(a, b);
    if (b->mantissa_float_len > a->mantissa_float_len)
        add_insignificant_zeros(b, a);

    int len_a = a->mantissa_float_len;
    int len_b = b->mantissa_float_len;

    int len_res = len_a + len_b;
    res->mantissa_float_len = len_res;

    int transfer = 0;
    int value = 0;
    int n = 1;
    for (int i = len_b - 1; i >= 0; i--)
    {
        int start = len_res - n;
        for (int j = len_a - 1; j >= 0; j--)
        {
            int tmp = b->mantissa_float[i] * a->mantissa_float[j];
            value = tmp % 10;
            res->mantissa_float[start] += (value + transfer) % 10;

            transfer = tmp / 10 + (value + transfer) / 10;

            if (res->mantissa_float[start] > 9)
            {
                res->mantissa_float[start] %= 10;
                transfer += 1;
            }
            start--;
        }
        n++;
        res->mantissa_float[start] += transfer; //Сброс transfer-a
        transfer = 0;
    }

    res->mantissa_int_len = 1;
    res->mantissa_int[0]  = 0;

    return TRUE;
}
