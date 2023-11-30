#include "specific.h"

bsa* bsa_init(void)
{
    bsa* b;

    b = (bsa*)neill_calloc(1, sizeof(bsa));

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

void* neill_calloc(int n, size_t size)
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
            free(b->p[i]);
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

    int rownum = get_rownum(indx);

    if(!(b->elements_exist[rownum])){
        int size = b->array_size[rownum];
        b->p[rownum] = (int*)neill_calloc(size, sizeof(int));
        b->elements_exist[rownum] = true;
    }
    int array_index = indx - (b->first_index[rownum]);

    b->p[rownum][array_index] = d;

    if(indx > b->max_index){
        b->max_index = indx;
    }

    return true;
}

int get_rownum(int indx)
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
// but with calloc vals are set to 0 so how do we know if it was set?
int* bsa_get(bsa* b, int indx)
{
    int rownum = get_rownum(indx);

    if(!b || !(b->elements_exist[rownum])){
        return NULL;
    }

    int array_index = indx - (b->first_index[rownum]);

    return &(b->p[rownum][array_index]);
    
}

void test(void)
{

}