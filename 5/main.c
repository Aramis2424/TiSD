#include "structures.h"
#include "io.h"
#include "array.h"
#include "timemem.h"
#include "list.h"

int main()
{
    setbuf(stdout, NULL);
    srand(time(NULL));
    int n = 1000;
    int interval = 100;
    int flag = 0;
    times_t t1 = { 1, 5 };
    times_t t2 = { 0, 3 };
    times_t t3 = { 0, 4 };
    times_t t4 = { 0, 1 };
    
    int num_command = -1;

    while (num_command != 0)
    {
        print_hello();
        printf_input();
        if (check_number(&num_command, 0, 5) != OK)
        {
            fflush(stdin);
            printf("Invalid input\n");

            print_hello();
        }
        else
        {
            fflush (stdin);
            switch (num_command)
            {
                case 1:
                    sim_array(n, interval, t1, t2, t3, t4);//, flag);
                    break;
                case 2:
                    flag = 0;
                    fflush(stdin);
                    sim_list(n, interval, t1, t2, t3, t4, flag);
                    fflush(stdin);
                    break;
                case 3:
                    printf("What interval to change?\n");
                    double l, r;
                    int c;
                    printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                    printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                    printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                    printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    if (check_number(&c, 1, 4) != OK)
                    {
                        fflush(stdin);
                        printf("Invalid input\n");
                        break;
                    }
                    else
                    {
                        printf("Input left and right borders: ");
                        int rc = scanf("%lf", &l);
                        if (rc != 1)
                        {
                            printf("Invalid input\n");
                            break;
                        }
                        rc = scanf("%lf", &r);
                        if (rc != 1)
                        {
                            printf("Invalid input\n");
                            break;
                        }
                        if (c == 1)
                        {
                            t1.min = l;
                            t1.max = r;
                        }
                        if (c == 2)
                        {
                            t2.min = l;
                            t2.max = r;
                        }
                        if (c == 3)
                        {
                            t3.min = l;
                            t3.max = r;
                        }
                        if (c == 4)
                        {
                            t4.min = l;
                            t4.max = r;
                        }
                        printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                        printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                        printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                        printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    }
                    break;  
                case 4:
                    printf("Output of compration\n");
                    memory_io();
                    break;               
            }
        }
    }
    return OK;
}
