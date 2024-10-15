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

    //matrix calculation test
    int m = 500, n = 500, p = 500;
    matrix *x = matrix_new(m, n);
    matrix *y = matrix_new(m, n);
    puts("\n");

    printf("행렬 덧셈 테스트:\n");
    measure_matrix_operation(matrix_add, x, y, "덧셈");


    printf("행렬 뺄셈 테스트:\n");
    measure_matrix_operation(matrix_sub, x, y, "뺄셈");


    matrix *z = matrix_new(n, p);
    printf("행렬 곱셈 테스트:\n");
    measure_matrix_operation(matrix_mult, x, y, "곱셈");


    printf("행렬 나눗셈 테스트:\n");
    measure_matrix_operation(matrix_div, x, y, "나눗셈");



    //smatrix calculation test
    smatrix_entry *s_a = smatrix_new(x);
    smatrix_entry *s_b = smatrix_new(y);

    printf("희소 행렬 덧셈 테스트:\n");
    measure_smatrix_operation(smatrix_add, s_a, s_b, "덧셈");
    printf("희소 행렬 뺄셈 테스트:\n");
    measure_smatrix_operation(smatrix_sub, s_a, s_b, "뺄셈");
    printf("희소 행렬 곱셈 테스트:\n");
    measure_smatrix_operation(smatrix_mult, s_a, s_b, "곱셈");

    matrix_free(x);
    matrix_free(y);
    matrix_free(z);
    smatrix_free(s_a);
    smatrix_free(s_b);
    return 0;
}
