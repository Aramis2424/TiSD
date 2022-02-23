
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE_VALUE 99999

#include "input.h"
#include "mult.h"
#include "normalization.h"

int main(void)
{
    printf("This program multiplies two real numbers\n");
    printf("Input two real numbers\n");
    printf("The maximum number length is 30 digits\n");
    printf("The maximum degree value is 99999\n");
    printf("Afer each number click enter\n");
    printf("'.' is equally ','\n");
    printf("'E' is equally 'e'\n\n");

    real_t a = { '\0', {0}, 0, {0}, 0, '\0', 0 };
    printf("                      1        10        20        30\n");
    printf("                      |--------|---------|---------|\n");
    printf("The first number is: ");
    int rc = real_scan(&a);
    if (rc != TRUE)
    {
        analysis_rc(rc);
        return rc;
    }
    del_insignificant_zeros(&a);
    normalization(&a);

    real_t b = { '\0', {0}, 0, {0}, 0, '\0', 0 };
    printf("                       1        10        20        30\n");
    printf("                       |--------|---------|---------|\n");
    printf("The second number is: ");
    rc = real_scan(&b);
    if (rc != TRUE)
    {
        analysis_rc(rc);
        return rc;
    }
    del_insignificant_zeros(&b);
    normalization(&b);

    real_t res = { '\0', {0}, 0, {0}, 0, '\0', 0 };
    if (is_zero(&a) || is_zero(&b))
    {
        printf("The result is: +0.0E+0\n");
        return EXIT_SUCCESS;
    }
    else
        real_mult(&a, &b, &res);

    del_insignificant_zeros(&res);
    normalization(&res);
    //Округление
    res_round(&res);
    del_insignificant_zeros(&res);

    if (abs(res.degree) > MAX_DEGREE_VALUE)
    {
        printf("Sorry, but the result is too big\n");
        return TOO_BIG_DEGREE;
    }

    printf("\n                  1        10        20        30\n");
    printf("                  |--------|---------|---------|\n");
    printf("The result is: ");
    real_print(res);
    return EXIT_SUCCESS;
}
