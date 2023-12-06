#include "specific.h"

bsa* bsa_init(void)
{
    bsa* b;

    b = (bsa*)_neill_calloc(1, sizeof(bsa));

    for(int i = 0; i < BSA_ROWS; i++){
        b->elements_exist[i] = false;
        if(i == 0){
            b->first_index[i] = i;
        }else if(i == 1){
            b->first_index[i] = i;
            b->last_index[i] = (1 << (i+1)) - LAST_INDX_ADJUST;
        }else{
            b->first_index[i] = (1 << i) - FIRST_INDX_ADJUST;
            b->last_index[i] = (1 << (i+1)) - LAST_INDX_ADJUST;
        }
        b->array_size[i] = b->last_index[i] - b->first_index[i] + 1;
        b->max_index = NULL_MAX_INDX;
    }

    return b;
}

void* _neill_calloc(int n, size_t size)
{
   void* v = calloc(n, size);
   if(v==NULL){
    fprintf(stderr, "Cannot calloc() space\n");
    exit(EXIT_FAILURE);
   }
   return v;
}

bool bsa_free(bsa* b)
{
    if(!b){
        return false;
    }

    for(int i = 0; i < BSA_ROWS; i++){
        if(b->elements_exist[i]){
            _tree_meta_free(b->p[i]);
        }
    }
    free(b);

    return true;
}

bool _tree_meta_free(tree_meta* tm)
{
    if(!tm){
        return false;
    }

    _tree_free(tm->top);
    free(tm);

    return true;
}

bool _tree_free(tree* t)
{
    if(!t){
        return false;
    }
    if(t->left){
        _tree_free(t->left);
    }
    if(t->right){
        _tree_free(t->right);
    }

    free(t);

    return true;

}

int bsa_maxindex(bsa* b)
{
    if(!b){
        return NULL_MAX_INDX;
    }
    return b->max_index;
}

void test(void)
{

}


