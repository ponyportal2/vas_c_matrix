#ifndef SRC_VAS_MATRIX_H_
#define SRC_VAS_MATRIX_H_
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e-9
#define SEVEN_PRECISION 0.0000001

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int vas_eq_matrix(matrix_t *A, matrix_t *B);

int vas_create_matrix(int rows, int columns, matrix_t *result);
void vas_remove_matrix(matrix_t *A);

int vas_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int vas_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int vas_mult_number(matrix_t *A, double number, matrix_t *result);

int vas_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int vas_transpose(matrix_t *A, matrix_t *result);
int vas_calc_complements(matrix_t *A, matrix_t *result);
int vas_determinant(matrix_t *A, double *result);
int vas_inverse_matrix(matrix_t *A, matrix_t *result);

int vas_get_minor(matrix_t *A, int elimIdxI, int elimIdxJ, matrix_t *result);
int vas_check_matrix_err(matrix_t *A);
void vas_copy_matrix(matrix_t *from, matrix_t *to);
void vas_print_matrix(matrix_t A);

// FILLERS:

void vas_fill_matrix_incr(matrix_t A, double x);
void vas_fill_matrix_single(matrix_t A, double x);
void vas_fill_matrix_random(matrix_t A, double x);

// HELPERS:

int vas_sumsub_helper(matrix_t *A, matrix_t *B, matrix_t *result, int flip);

#endif  // SRC_VAS_MATRIX_H_
