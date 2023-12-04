#pragma once

#include "../bsa.h"

#define MAXBUFF 20

//array structure
struct array {
    int* a;
    bool* is_assigned;
    int max_array_index;
    int n_assigned;
};

typedef struct array array;

//Stolen from Neill (https://github.com/csnwc/ADTs/blob/main/General/general.c)
void* _neill_calloc(int n, size_t size);

//return row number of pointer which points to the array which contains index
int _get_rownum(int indx);

//return index of array which holds indx
int _get_array_index(int indx, bsa* b, int rownum);

//free array
bool _array_free(array* a);

// returns new max array index for use when previous max is deleted
int _new_max_array_index(array* a);

// returns new max bsa index for use when previous max is deleted
int _new_max_bsa_index(bsa* b);
