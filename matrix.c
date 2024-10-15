#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "nstdmath.h"
#include <time.h>
#define ENTRY_MAX 16

matrix* matrix_new(int m, int n)
{
    matrix *mat = malloc(sizeof(matrix));
    mat->m = m;
    mat->n = n;
    mat->mem = malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++)
        mat->mem[i] = malloc(sizeof(int) * n);

    return mat;
}

void matrix_free(matrix *mat)
{
    for (int i = 0; i < mat->m; i++)
        free(mat->mem[i]);
    free(mat->mem);
    free(mat);
}

// matrix_init: completely zeroes-out the given matrix.
void matrix_init(matrix *mat)
{
    for (int i = 0; i < mat->m; i++)
    {
        for (int j = 0; j < mat->n; j++)
        {
            mat->mem[i][j] = 0;
        }
    }
}

// matrix_rand: randomizes the entries of the given matrix.
void matrix_rand(matrix *mat)
{
    for (int i = 0; i < mat->m; i++)
    {
        for (int j = 0; j < mat->n; j++)
        {
            mat->mem[i][j] = rand() % ENTRY_MAX - ENTRY_MAX/2;
        }
    }
}

// matrix_nzcnt(non-zero count): returns the number of non-zero entries in the given matrix.
int matrix_nzcnt(matrix *mat)
{
    int cnt = 0;

    for (int i = 0; i < mat->m; i++)
    {
        for (int j = 0; j < mat->n; j++)
        {
            cnt += mat->mem[i][j] != 0;
        }
    }

    return cnt;
}

matrix* matrix_add(matrix *mat_a, matrix *mat_b)
{
    matrix *res = matrix_new(mat_a->m, mat_a->n);

    for (int i = 0; i < mat_a->m; i++)
    {
        for (int j = 0; j < mat_a->n; j++)
        {
            res->mem[i][j] = mat_a->mem[i][j] + mat_b->mem[i][j];
        }
    }

    return res;
}

matrix* matrix_sub(matrix *mat_a, matrix *mat_b)
{
    matrix *res = matrix_new(mat_a->m, mat_a->n);

    for (int i = 0; i < mat_a->m; i++)
    {
        for (int j = 0; j < mat_a->n; j++)
        {
            res->mem[i][j] = mat_a->mem[i][j] - mat_b->mem[i][j];
        }
    }

    return res;
}

matrix* matrix_mult(matrix *mat_a, matrix *mat_b)
{
    matrix *res = matrix_new(mat_a->m, mat_b->n);

    for (int i = 0; i < mat_a->m; i++)
    {
        for (int j = 0; j < mat_b->n; j++)
        {
            // dot product.
            int dprod = 0;
            for (int k = 0; k < mat_a->n; k++)
                dprod += mat_a->mem[i][k] * mat_b->mem[k][j];

            res->mem[i][j] = dprod;
        }
    }

    return res;
}

matrix* matrix_div(matrix *mat_a, matrix *mat_b)
{
    matrix *res = matrix_new(mat_a->m, mat_a->n);

    for (int i = 0; i < mat_a->m; i++)
    {
        for (int j = 0; j < mat_a->n; j++)
        {
            res->mem[i][j] = nstd_idiv(mat_a->mem[i][j], mat_b->mem[i][j]);
        }
    }

    return res;
}

void matrix_print(matrix *mat)
{
    for (int i = 0; i < mat->m; i++)
    {
        for (int j = 0; j < mat->n; j++)
            printf("%d ", mat->mem[i][j]);

        puts("");
    }
}

void measure_matrix_operation(matrix* (*matrix_op)(matrix*, matrix*),
                                   matrix *a, matrix *b, const char *operation_name) {
    for (int i = 0; i < 5; i++) {
        matrix_rand(a);
        matrix_rand(b);

        clock_t start = clock();  // 시작 시간 측정

        // 전달된 연산 함수 실행
        matrix *res = matrix_op(a, b);

        clock_t end = clock();  // 끝 시간 측정

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;  // 실행 시간 계산
        printf("%dx%d 행렬에 대한 %s: %f 초\n", a->m, a->n, operation_name, time_taken);

        matrix_free(res);  // 결과 행렬 메모리 해제
    }
}
