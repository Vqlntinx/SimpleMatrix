#ifndef __SMATRIX_H
#define __SMATRIX_H

#include "matrix.h"

// sparse matrix entry.
struct smatrix_entry
{
    // row, column, value;
    int r, c, v;
};

typedef struct smatrix_entry smatrix_entry;

smatrix_entry* smatrix_new(matrix*);
void smatrix_free(smatrix_entry*);
smatrix_entry* smatrix_trans(smatrix_entry*);
matrix* smatrix_add(smatrix_entry*, smatrix_entry*);
matrix* smatrix_sub(smatrix_entry*, smatrix_entry*);
matrix* smatrix_mult(smatrix_entry*, smatrix_entry*);
void smatrix_print(smatrix_entry*);
void measure_smatrix_operation(matrix* (*smatrix_op)(smatrix_entry*, smatrix_entry*), smatrix_entry *s_a, smatrix_entry *s_b, const char *operation_name);
#endif
