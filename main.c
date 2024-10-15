#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "smatrix.h"

int main()
{
    srand(time(0));

    matrix *a = matrix_new(3, 3);
    matrix *b = matrix_new(3, 3);
    matrix_rand(a);
    matrix_rand(b);

    puts("a matrix");
    matrix_print(a);
    puts("b matrix");
    matrix_print(b);

    matrix *c = matrix_add(a, b);
    matrix *d = matrix_sub(a, b);
    matrix *e = matrix_mult(a, b);

    puts("c matrix");
    matrix_print(c);
    puts("d matrix");
    matrix_print(d);
    puts("e matrix");
    matrix_print(e);

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);
    matrix_free(d);
    matrix_free(e);

    int m = 1000, n = 1000;
    matrix *x = matrix_new(m, n);
    matrix *y = matrix_new(m, n);
    puts("\n");

    printf("Çà·Ä µ¡¼À Å×½ºÆ®:\n");
    measure_matrix_operation(matrix_add, x, y, "µ¡¼À");


    printf("Çà·Ä »¬¼À Å×½ºÆ®:\n");
    measure_matrix_operation(matrix_sub, x, y, "»¬¼À");


    matrix *z = matrix_new(n, n);
    printf("Çà·Ä °ö¼À Å×½ºÆ®:\n");
    measure_matrix_operation(matrix_mult, x, y, "°ö¼À");


    printf("Çà·Ä ³ª´°¼À Å×½ºÆ®:\n");
    measure_matrix_operation(matrix_div, x, y, "³ª´°¼À");

    matrix_free(x);
    matrix_free(y);
    matrix_free(z);

    return 0;
}