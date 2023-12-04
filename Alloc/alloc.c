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
            b->last_index[i] = (1 << (i+1)) - 2;
        }else{
            b->first_index[i] = (1 << i) - 1;
            b->last_index[i] = (1 << (i+1)) - 2;
        }
        b->array_size[i] = b->last_index[i] - b->first_index[i] + 1;
        b->max_index = -1;

        //printf("Row %i: first = %i, last = %i, size = %i\n", i, b->first_index[i], b->last_index[i], b->array_size[i]);
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
            _array_free(b->p[i]);
        }
    }
    free(b);

    return true;
}

bool bsa_set(bsa* b, int indx, int d)
{
    if(!b){
        return false;
    }

    int rownum = _get_rownum(indx);

    if(!(b->elements_exist[rownum])){
        int size = b->array_size[rownum];
        b->p[rownum] = (array*)_neill_calloc(1, sizeof(array));
        b->p[rownum]->a = (int*)_neill_calloc(size, sizeof(int));
        b->p[rownum]->is_assigned = (bool*)_neill_calloc(size, sizeof(bool));
        b->p[rownum]->max_array_index = -1;
        b->elements_exist[rownum] = true;
        b->p[rownum]->n_assigned = 0;
    }
    int array_index = _get_array_index(indx, b, rownum);

    b->p[rownum]->a[array_index] = d;
    if(!b->p[rownum]->is_assigned[array_index]){
        b->p[rownum]->n_assigned++;
        b->p[rownum]->is_assigned[array_index] = true;
    }
    if(array_index > b->p[rownum]->max_array_index){
        b->p[rownum]->max_array_index = array_index;
    }

    if(indx > b->max_index){
        b->max_index = indx;
    }

    return true;
}

int _get_array_index(int indx, bsa* b, int rownum){
    int array_index = indx - (b->first_index[rownum]);

    return array_index;
}

int _get_rownum(int indx)
{
    int rownum = -1, indx_cpy = indx+1;

    do{
        indx_cpy = indx_cpy >> 1;
        rownum++;
    } while(indx_cpy > 0);

    return rownum;
}

int bsa_maxindex(bsa* b)
{
    if(!b){
        return -1;
    }
    return b->max_index;
}

int* bsa_get(bsa* b, int indx)
{
    int rownum = _get_rownum(indx);
    int array_index = _get_array_index(indx, b, rownum);

    if(!b || !(b->elements_exist[rownum]) ||
     !b->p[rownum]->is_assigned[array_index]){
        return NULL;
    }

    return &(b->p[rownum]->a[array_index]);    
}

bool bsa_tostring(bsa* b, char* str)
{
    if(!b || !str){
        return false;
    }
    //make input string empty
    strcpy(str, "");
    int max_index = b->max_index;
    int rownum = _get_rownum(max_index);
    char buffer[MAXBUFF];

    for(int i = 0; i <= rownum; i++){
        strcat(str, "{");
        if(b->elements_exist[i]){
            for(int j = 0; j <= b->p[i]->max_array_index; j++){
                if(b->p[i]->is_assigned[j]){
                    if(j == b->p[i]->max_array_index){
                        sprintf(buffer, "[%d]=%d", (j+b->first_index[i]), 
                        b->p[i]->a[j]);
                    }else{
                        sprintf(buffer, "[%d]=%d ", (j+b->first_index[i]),
                        b->p[i]->a[j]);
                    }  
                    strcat(str, buffer);
                }
            }
        }
        strcat(str, "}");
    }
    if(strcmp(str, "{}") == 0){
        strcpy(str, "");
    }

    //printf("str = %s\n", str);
    return true;
}

bool bsa_delete(bsa* b, int indx)
{
    int rownum = _get_rownum(indx);
    int array_index = _get_array_index(indx, b, rownum);

    if(!b || !b->p[rownum] || !b->p[rownum]->is_assigned[array_index]){
        return false;
    }
    b->p[rownum]->is_assigned[array_index] = false;
    b->p[rownum]->n_assigned--;

    bool array_freed = false;
    if(b->p[rownum]->n_assigned == 0){
        _array_free(b->p[rownum]);
        b->elements_exist[rownum] = false;
        array_freed = true;
    }

    if(!array_freed){
        if(array_index == b->p[rownum]->max_array_index){
            b->p[rownum]->max_array_index = _new_max_array_index(b->p[rownum]);
        }
    }

    if(indx == b->max_index){
        b->max_index = _new_max_bsa_index(b);
    }
    return true;
}

bool _array_free(array* a)
{
    if(!a){
        return false;
    }
    free(a->a);
    free(a->is_assigned);
    free(a);

    return true;
}

int _new_max_bsa_index(bsa* b)
{
    
    int max_index = -1;
    int x;

    for(int i = 0; i < BSA_ROWS; i++){
        if(b->elements_exist[i]){
            x = b->p[i]->max_array_index;
            x += b->first_index[i];
            if(x > max_index){
                max_index = x;
            }
        }
    }
    return max_index;
}

int _new_max_array_index(array* a)
{
    int new_max;
    bool found = false;
    
    for(int i = a->max_array_index; !found; i--){
        if(a->is_assigned[i]){
            new_max = i;
            found = true;
        }
    }
    return new_max;
}

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc)
{
    for(int i = 0; i < BSA_ROWS; i++){
        if(b->elements_exist[i]){
            for(int j = 0; j <= b->p[i]->max_array_index; j++){
                if(b->p[i]->is_assigned[j]){
                    func(&b->p[i]->a[j], acc);
                }
            }
        }
        
    }
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

    assert(!_array_free(b->p[0]));
    assert(!_array_free(b->p[13]));

    bsa_set(b, 0, 5);
    assert(_array_free(b->p[0]));
    b->elements_exist[0] = false;

    bsa_set(b, 4, 5);
    assert(_new_max_array_index(b->p[2]) == 1);
    assert(_new_max_bsa_index(b) == 4);
    bsa_set(b, 6, 5);
    assert(_new_max_array_index(b->p[2]) == 3);
    assert(_new_max_bsa_index(b) == 6);
    bsa_set(b, 100, 5);
    assert(_new_max_array_index(b->p[6]) == 37);
    assert(_new_max_bsa_index(b) == 100);
    bsa_set(b, 80, 5);
    assert(_new_max_array_index(b->p[6]) == 37);

    bsa_free(b);

}