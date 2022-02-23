#include <ctype.h>
#include "functions.h"
#include "errors.h"

int is_num(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return FALSE;
    return TRUE;
}
