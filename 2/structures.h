#ifndef STRUCTURES_H
#define STRUCTURES_H

#define TRUE 1
#define FALSE 0

#define WORD_LEN 100
#define LINE_LEN 500
#define ARR_SIZE 2000

typedef struct type_flat
{
    char street[WORD_LEN];
    int house;
    int room;
}flat_t;

typedef struct type_dormitory
{
    int dormitory;
    int room;
}dormitory_t;

typedef union housing
{
    flat_t flat;
    dormitory_t dormitory;
}housing_t;

typedef struct students
{
    char surname[WORD_LEN];
    char name[WORD_LEN];
    int group;
    int gender;
    int age;
    double avg_score;
    int year;
    int type;
    housing_t type_housing;
}students_t;

typedef struct keys
{
    int age;
    int id;
}keys_t;

typedef struct table
{
    students_t student;
    keys_t key;
}table_t;

#endif
