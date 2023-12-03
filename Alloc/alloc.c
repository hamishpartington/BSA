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
            free(b->p[i]->a);
            free(b->p[i]->is_assigned);
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
        b->p[rownum] = (array*)neill_calloc(1, sizeof(array));
        b->p[rownum]->a = (int*)neill_calloc(size, sizeof(int));
        b->p[rownum]->is_assigned = (bool*)neill_calloc(size, sizeof(bool));
        b->p[rownum]->max_array_index = -1;
        b->elements_exist[rownum] = true;
        b->p[rownum]->n_assigned = 0;
    }
    int array_index = indx - (b->first_index[rownum]);

    b->p[rownum]->a[array_index] = d;
    b->p[rownum]->n_assigned++;
    b->p[rownum]->is_assigned[array_index] = true;
    if(array_index > b->p[rownum]->max_array_index){
        b->p[rownum]->max_array_index = array_index;
    }

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

    return &(b->p[rownum]->a[array_index]);    
}

bool bsa_tostring(bsa* b, char* str)
{
    if(!b){
        return false;
    }
    //make input string empty
    strcpy(str, "");
    int max_index = b->max_index;
    int rownum = get_rownum(max_index);
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
    //printf("%s\n", str);
    return true;
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
// bool bsa_delete(bsa* b, int indx)
// {

// }

void test(void)
{

}