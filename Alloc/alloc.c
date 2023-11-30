#include "specific.h"

bsa* bsa_init(void)
{
    bsa* b;

    b = (bsa*)neill_calloc(1, sizeof(bsa));

    for(int i = 0; i < BSA_ROWS; i++){
        b->elements_exist[i] = false;
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

void test(void)
{

}