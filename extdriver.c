#include "Extension/specific.h"

int main(void)
{

   test();

   // A NULL BSA has size zero
   assert(bsa_maxindex(NULL)==-1);

   // Initialise
   bsa* b = bsa_init();
   assert(b);
   assert(bsa_maxindex(b)==-1);

   // Set some values
   assert(bsa_set(b, 0, 4));
   assert(bsa_maxindex(b)==0);
   // Reset existing value
   assert(bsa_set(b, 0, 0));
   assert(bsa_set(b, 15, 15));

   // Get some values tbsa've already been set
   int* p = bsa_get(b, 0);
   assert(p);
   assert(*p == 0);
   p = bsa_get(b, 15);
   assert(p);
   assert(*p == 15);

   // Get an unset value 
   p = bsa_get(b, 1);
   assert(!p);
   p = bsa_get(b, 1024);
   assert(!p);

   assert(bsa_set(b, 100, 100));
   assert(bsa_maxindex(b)==100);
   // Once resized, using a get is OK
   p = bsa_get(b, 100);
   assert(p);
   assert(*p == 100);
   // Retest values from BSA before resize
   p = bsa_get(b, 15);
   assert(p);
   assert(*p == 15);

   // Let's do some deleting

   // Cell not not used, can't delete it
   assert(!bsa_delete(b, 99));
   // Cell is used, can delete it
   assert(bsa_delete(b, 100));
   assert(bsa_maxindex(b)==15);
   
   // Cell is used, can delete it
   assert(bsa_delete(b, 15));
   assert(bsa_maxindex(b)==0);

   // Delete last element left
   assert(bsa_delete(b, 0));
   assert(bsa_maxindex(b)<0);

  
   bsa_free(b);

   // foreach - use it to compute product of numbers, and also to double each one
   b = bsa_init();
   bsa_set(b, 1, 1);
   bsa_set(b, 2, 2);
   bsa_set(b, 3, 3);
   int acc = 1;
   bsa_foreach(times, b, &acc);
   assert(acc==6);

   bsa_foreach(twice, b, &acc);
   bsa_free(b);

   return 0;
}

   
