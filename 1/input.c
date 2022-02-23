#include "input.h"
#include "mult.h"
#include "normalization.h"

int real_scan(real_t *number)
{
    int count_int = 0;
    int count_float = 0;
    int int_part = 1;
    int float_part = 0;

    char symbol = getchar();

    //Проверка символа на знак
    if (symbol == '+')
        number->mantissa_sign = '+';
    else if (symbol == '-')
        number->mantissa_sign = '-';
    else if (isdigit(symbol))
    {
        number->mantissa_sign = '+';
        number->mantissa_int[count_int] = ctoi(symbol);
        count_int++;
        if (symbol == '0')
            count_int--;
    }
    else if (symbol == '.' || symbol == ',')
    {
        number->mantissa_sign = '+';
        int_part = 0;
        float_part = 1;
    }
    else
        return ERROR_WRONG_SYMBOL;

    //Чтение целой части
    if (int_part)
        while ((symbol = getchar()) != EOF)
        {
            if (symbol == '.' || symbol == ',')
            {
                float_part = 1;
                break;
            }
            if (symbol == '\n' || symbol == 'E' || symbol == 'e')
                break;
            if (count_int >= MANTISSA_LEN)
                return EXIT_TOO_LONG_NUMBER;
            if (!isdigit(symbol))
                return ERROR_WRONG_SYMBOL;
            number->mantissa_int[count_int] = ctoi(symbol);
            count_int++;
        }
    number->mantissa_int_len = count_int;

    //Чтение дробной части
    if (float_part)
        while ((symbol = getchar()) != EOF)
        {
            if (symbol == '\n' || symbol == 'E' || symbol == 'e')
                break;
            if (count_int + count_float >= MANTISSA_LEN)
                return EXIT_TOO_LONG_NUMBER;
            if (!isdigit(symbol))
                return ERROR_WRONG_SYMBOL;
            number->mantissa_float[count_float] = ctoi(symbol);
            count_float++;
        }
    if (float_part)
        number->mantissa_float_len = count_float;
    else
        number->mantissa_float_len = 1;

    if (symbol == '\n')
    {
        number->degree_sign = '+';
        number->degree = 0;
        return TRUE;
    }

    //Чтение порядка
    symbol = getchar();
    int count_degree = 0;
    if (symbol == '+')
        number->degree_sign = '+';
    else if (symbol == '-')
        number->degree_sign = '-';
    else if (isdigit(symbol))
    {
        number->degree_sign = '+';
        number->degree = ctoi(symbol);
        count_degree = 1;
    }
    else
        return ERROR_WRONG_SYMBOL;
    int ratio = 10;
    while ((symbol = getchar()) != EOF && symbol != '\n')
    {
        if (count_degree >= DEGREE_LEN)
            return TOO_BIG_DEGREE;
        if (!isdigit(symbol))
            return ERROR_WRONG_SYMBOL;
        number->degree = number->degree * ratio + ctoi(symbol);
        count_degree++;
    }
    return TRUE;
}

void arr_print(int arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d", arr[i]);
}

void real_print(real_t a)
{
    printf("%c", a.mantissa_sign);
    for (int i = 0; i < a.mantissa_int_len; i++)
        printf("%d", a.mantissa_int[i]);
    printf(".");
    for (int i = 0; i < a.mantissa_float_len; i++)
        printf("%d", a.mantissa_float[i]);
    printf("E");
    printf("%c", a.degree_sign);
    printf("%d", a.degree);
    printf("\n");
}

int analysis_rc(int rc)
{
    if (rc == 2)
    {
        printf("Sorry, but you have input wrong symbol\n");
        return ERROR_WRONG_SYMBOL;
    }
    if (rc == 3)
    {
        printf("Sorry, but you have input too long mantissa\n");
        return EXIT_TOO_LONG_NUMBER;
    }
    if (rc == 4)
    {
        printf("Sorry, but you have input too long degree\n");
        return EXIT_TOO_LONG_NUMBER;
    }
    return TRUE;
}
