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
    int array_size[BSA_ROWS];
};

//struct with tree_metadata and pointer to top of tree
struct tree_meta {
    struct tree* top;
    int max_array_index;
    int n_assigned;
};

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

bool _tree_meta_free(tree_meta* tm);

bool _tree_free(tree* t);

