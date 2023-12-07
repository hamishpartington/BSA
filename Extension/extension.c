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
    }

    b->max_index = NULL_MAX_INDX;

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
    if(tm->n_assigned > 0){
        _tree_free(tm->top);
    }
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

bool bsa_set(bsa* b, int indx, int d)
{
    if(!b){
        return false;
    }

    int rownum = _get_rownum(indx);

    if(!(b->elements_exist[rownum])){
        b->p[rownum] = _tree_init();
        b->elements_exist[rownum] = true;
    }
    int array_index = _get_array_index(indx, b, rownum);

    b->p[rownum]->top = _tree_set(b->p[rownum]->top, d, array_index, &b->p[rownum]->n_assigned);
    b->p[rownum]->n_assigned++;

    if(b->p[rownum]->max_array_index < array_index){
        b->p[rownum]->max_array_index = array_index;
    }

    if(indx > b->max_index){
        b->max_index = indx;
    }
    return true;
}

int _get_array_index(int indx, bsa* b, int rownum)
{
    int array_index = indx - (b->first_index[rownum]);

    return array_index;
}

int _get_rownum(int indx)
{
    int rownum = -1, indx_cpy = indx+FIRST_INDX_ADJUST;

    do{
        indx_cpy = indx_cpy >> 1;
        rownum++;
    } while(indx_cpy > 0);

    return rownum;
}

tree_meta* _tree_init(void)
{
    tree_meta* tm;

    tm = (tree_meta*)_neill_calloc(1, sizeof(tree_meta));
    tm->max_array_index = -1;
    tm->n_assigned = 0;

    return tm;
}

tree* _tree_set(tree* t, int d, int array_index, int* n_assigned)
{
    tree* f;

    if(!t){
        f = (tree*)_neill_calloc(1, sizeof(tree));
        f->data = d;
        f->index = array_index;

        return f;
    }
    if(array_index < t->index){
        t->left = _tree_set(t->left, d, array_index, n_assigned);
    }
    if(array_index > t->index){
        t->right = _tree_set(t->right, d, array_index, n_assigned);
    }

    if(array_index == t->index){
        t->data = d;
        *n_assigned += -1;
    }

    return t;
}

int* bsa_get(bsa* b, int indx)
{
    int rownum = _get_rownum(indx);
    int array_index = _get_array_index(indx, b, rownum);

    if(!b || !(b->elements_exist[rownum])){
        return NULL;
    }

    int* x = _tree_get(b->p[rownum]->top, array_index);

    return x;    
}

int* _tree_get(tree* t, int array_index)
{
    int* x = NULL;

    if(!t)
    {
        return NULL;
    }
    if(array_index == t->index)
    {
        x = &t->data;
    }
    if(array_index < t->index)
    {
        x = _tree_get(t->left, array_index);
    }
        if(array_index > t->index)
    {
        x = _tree_get(t->right, array_index);
    }

    return x;
}

bool bsa_delete(bsa* b, int indx)
{
    if(!b){
        return false;
    }
    bool deleted = false;
    int rownum = _get_rownum(indx);
    int array_index = _get_array_index(indx, b, rownum);

    b->p[rownum]->top = _tree_delete(b->p[rownum]->top, array_index, &deleted);

    if(deleted){
        b->p[rownum]->n_assigned += -1;
    }

    if(array_index == b->p[rownum]->max_array_index && 
        b->p[rownum]->n_assigned > 0){
            b->p[rownum]->max_array_index = _new_max_array_index(b->p[rownum]->top);
    }
    if(b->p[rownum]->n_assigned == 0){
        b->elements_exist[rownum] = false;
        free(b->p[rownum]);
    }

    if(indx == b->max_index){
        b->max_index = _new_max_bsa_index(b);
    }
    return deleted;

}

int _new_max_array_index(tree* t)
{   
    int max = t->index;
    while(t->right){
        t = t->right;
        max = t->index;
    }
    return max;
}

int _new_max_bsa_index(bsa* b)
{
    
    int max_index = -1;

    for(int i = BSA_ROWS-1; i >= 0 && max_index == -1; i--){
        if(b->elements_exist[i]){
            max_index = b->p[i]->max_array_index;
            max_index += b->first_index[i];
        }
    }
    return max_index;
}

tree* _tree_delete(tree* t, int array_index, bool *deleted)
{
    if(!t){
        return t;
    }
    if(array_index < t->index){
        t->left = _tree_delete(t->left, array_index, deleted);
        return t;
    }
    if(array_index > t->index){
        t->right = _tree_delete(t->right, array_index, deleted);
        return t;
    }

    tree* temp;

    if(!t->right){
        temp = t->left;
        free(t);
        *deleted = true;
        return temp;
    }else if(!t->left){
        temp = t->right;
        free(t);
        *deleted = true;
        return temp;
    }else{
        tree* parent = t;
        tree* child = t->right;
        *deleted = true;
        while(child->left){
            parent = child;
            child = child->left;
        }
        if(parent != t){
            parent->left = child->right;
        }else{
            parent->right = child->right;
        }

        t->data = child->data;
        t->index = child->index;

        free(child);
        return t;
    }
}

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc)
{
    for(int i = 0; i < BSA_ROWS; i++){
        if(b->elements_exist[i]){
            _tree_foreach(func, b->p[i]->top, acc);
        }
    }
}

void _tree_foreach(void (*func)(int* p, int* n), tree* t, int* acc)
{
    if(!t){
        return;
    }
    _tree_foreach(func, t->left,  acc);
    func(&t->data, acc);
    _tree_foreach(func, t->right, acc);

}

void test(void)
{
    assert(_get_rownum(0) == 0);
    assert(_get_rownum(2) == 1);
    assert(_get_rownum(3) == 2);
    assert(_get_rownum(14) == 3);
    assert(_get_rownum(31) == 5);
    assert(_get_rownum(2046) == 10);
    assert(_get_rownum(2047) == 11);

    bsa* b = bsa_init();

    assert(_get_array_index(0, b, 0) == 0);
    assert(_get_array_index(14, b, 3) == 7);
    assert(_get_array_index(2046, b, 10) == 1023);
    assert(_get_array_index(64, b, 6) == 1);
    assert(_get_array_index(8191, b, 13) == 0);
    assert(_get_array_index(8190, b, 12) == 4095);

    assert(!_tree_meta_free(b->p[0]));
    assert(!_tree_meta_free(b->p[13]));

    bsa_set(b, 0, 5);
    bsa_set(b, 4, 6);
    assert(_tree_meta_free(b->p[2]));
    b->elements_exist[2] = false;

    bsa_set(b, 4, 5);
    assert(_new_max_array_index(b->p[2]->top) == 1);
    assert(_new_max_bsa_index(b) == 4);
    bsa_set(b, 6, 5);
    assert(_new_max_array_index(b->p[2]->top) == 3);
    assert(_new_max_bsa_index(b) == 6);
    bsa_set(b, 100, 5);
    assert(_new_max_array_index(b->p[6]->top) == 37);
    assert(_new_max_bsa_index(b) == 100);
    bsa_set(b, 80, 5);
    assert(_new_max_array_index(b->p[6]->top) == 37);

    tree_meta* tm = _tree_init();
    
    tm->top = _tree_set(tm->top, 40, 500, &tm->n_assigned);
    tm->n_assigned++;
    tm->top = _tree_set(tm->top, 23, 5, &tm->n_assigned);
    tm->n_assigned++;
    tm->top = _tree_set(tm->top, 34, 777, &tm->n_assigned);
    tm->n_assigned++;
    assert(*_tree_get(tm->top, 500) == 40);
    assert(*_tree_get(tm->top, 5) == 23);
    assert(*_tree_get(tm->top, 777) == 34);

    int acc = 1;
    _tree_foreach(times, tm->top, &acc);
    assert(acc==31280);

    _tree_foreach(twice, tm->top, &acc);
    assert(*_tree_get(tm->top, 500) == 80);
    assert(*_tree_get(tm->top, 5) == 46);
    assert(*_tree_get(tm->top, 777) == 68);

    _tree_meta_free(tm);

    bsa_free(b);

}

//functions from neill for testing foreach
void times(int* p, int* n)
{
   *n = *n * *p;
}

void twice(int* p, int* n)
{
   // Need to use n to switch off warnings :-(
   *n = 0;
   *p = *p * 2;
}

