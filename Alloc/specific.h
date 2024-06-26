#pragma once

#include "../bsa.h"

#define MAXBUFF 20
#define FIRST_INDX_ADJUST 1
#define LAST_INDX_ADJUST 2
#define NULL_MAX_INDX -1

struct bsa {
    struct array* p[BSA_ROWS];
    bool elements_exist[BSA_ROWS];
    int max_index;
    int first_index[BSA_ROWS];
    int last_index[BSA_ROWS];
    int array_size[BSA_ROWS];
};

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

// sub function to bsa_to_string which concats members of each array to the 
// overall string
void _concat_to_string(bsa* b, char* str, int rownum);

//sub function to bsa_init: create an empty array
array* _array_init(int size);

//sub function to bsa_set: set a[array_index] to d;
bool _array_set(array* a, int d, int array_index);
