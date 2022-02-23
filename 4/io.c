#include <stdio.h>
#include "io.h"

void intro_void(void)
{
    printf("Hello!\n");
    printf("This program simulates the operation of the stack.\n");
    printf("You can do: \n");
    printf("   1)Enter a word on the stack;\n");
    printf("   2)Print the words;\n");
    printf("   3)Delete the words.\n\n");
}

void menu_print(void)
{
    printf("Menu:\n");
    printf("   1)Add word;\n");
    printf("   2)Print the words in direct order;\n");
    printf("   3)Print the words in reverse order;\n");
    printf("   4)Del word;\n");
    printf("   5)Print the free field of memory;\n");
    printf("   6)Clear stack;\n");
    printf("   7)Compare time of work;\n");
    printf("   0)Exit.\n");
    printf("Your choice is: ");
}
