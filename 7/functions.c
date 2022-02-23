#include <ctype.h>
#include <stdio.h>
#include <inttypes.h>
#include "functions.h"
#include "errors.h"
#include "processing.h"

int is_num(const char *str)
{
    int flag = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]) && flag)
            return FALSE;
        else
            if (str[i] == '-')
                flag = 1;
    }

    return TRUE;
}
