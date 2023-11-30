#pragma once

#include "../bsa.h"

//Stolen from Neill (https://github.com/csnwc/ADTs/blob/main/General/general.c)
void* neill_calloc(int n, size_t size);

//return row number of pointer which points to the array which contains index
int get_rownum(int indx);

