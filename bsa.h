/* Binary Sparse Arrays */
#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define BSA_ROWS 30

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

typedef struct bsa bsa;
typedef struct array array;

// Create an empty BSA
bsa* bsa_init(void);

// Set element at index indx with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d);

// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx);

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx);

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b);

// Returns stringified version of structure
// Each row has its elements printed between {}, up to the maximum index.
// Rows after the maximum index are ignored.
bool bsa_tostring(bsa* b, char* str);

// Clears up all space used
bool bsa_free(bsa* b);

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc);

// You'll this to test the other functions you write
void test(void);
