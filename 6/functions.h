#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <inttypes.h>

int is_num(const char *str);
int64_t tick(void);
int64_t getFileSize(const char* file_name);
int next_prime(int n);
int prev_prime(int n);

#endif
