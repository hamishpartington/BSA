#pragma once

#include "../bsa.h"

#define FIRST_INDX_ADJUST 1
#define LAST_INDX_ADJUST 2
#define NULL_MAX_INDX -1

//bsa structure
struct bsa {
    struct tree_meta* p[BSA_ROWS];
    bool elements_exist[BSA_ROWS];
    int max_index;
    int first_index[BSA_ROWS];
    int last_index[BSA_ROWS];
};

//struct with tree_metadata and pointer to top of tree
struct tree_meta {
    struct tree* top;
    int max_array_index;
    int n_assigned;
};

// binary tree structure
struct tree {
    int data;
    int index;
    struct tree* left;
    struct tree* right;
};

typedef struct tree tree;
typedef struct tree_meta tree_meta;

//Stolen from Neill (https://github.com/csnwc/ADTs/blob/main/General/general.c)
void* _neill_calloc(int n, size_t size);
//sub function to bsa_free which frees tree_meta structure
bool _tree_meta_free(tree_meta* tm);
//sub function to _tree_meta_free which frees underlying tree
bool _tree_free(tree* t);
//return row number of pointer which points to the array which contains index
int _get_rownum(int indx);
//return index of array which holds indx
int _get_array_index(int indx, bsa* b, int rownum);
//sub function to bsa_set which is called to initiate tree_meta structure if no
// data exists in that row
tree_meta* _tree_init(void);
//sub function to bsa_set appends node to tree 
tree* _tree_set(tree* t, int d, int array_index, int* n_assigned);
// sub function to bsa_get which returns data from node with array_index
int* _tree_get(tree* t, int array_index);
// sub function to bsa_delete which deletes node at array_index and restructures
// tree if necessary
tree* _tree_delete(tree* t, int array_index, bool *deleted);
// returns new max array index for use when previous max is deleted
int _new_max_array_index(tree* t);
// returns new max bsa index for use when previous max is deleted
int _new_max_bsa_index(bsa* b);
//subfunction to bsa_for which applies func to data at each node of tree working
// from lowest to highest index
void _tree_foreach(void (*func)(int* p, int* n), tree* t, int* acc);

//neills functions for testing foreach
void times(int* p, int* n);
void twice(int* p, int* n);

