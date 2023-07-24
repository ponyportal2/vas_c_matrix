#include "vas_matrix.h"

int vas_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows < 1 || columns < 1) error = 1;
  if (error != 1) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) error = 1;
    if (error != 1) {
      for (int i = 0; i < rows && error != 1; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) error = 1;
      }
    }
  }
  if (error == 1) {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

void vas_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i]) free(A->matrix[i]);
  }
  if (A->matrix) free(A->matrix);
  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

int vas_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return vas_sumsub_helper(A, B, result, 1);
}

int vas_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return vas_sumsub_helper(A, B, result, -1);
}

int vas_sumsub_helper(matrix_t *A, matrix_t *B, matrix_t *result, int flip) {
  int error = 0;
  if (vas_check_matrix_err(A) || vas_check_matrix_err(B) || result == NULL) {
    error = 1;
  }
  if (error < 1) {
    if ((A->rows != B->rows) || (A->columns != B->columns)) error = 2;
    if (error < 1) {
      if (vas_create_matrix(A->rows, A->columns, result) > 0) error = 1;
      if (error < 1) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * flip);
          }
        }
      }
    }
  }
  return error;
}

int vas_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (vas_check_matrix_err(A) || result == NULL) error = 1;
  if (error != 1) {
    if (vas_create_matrix(A->rows, A->columns, result) > 0) error = 1;
    if (error != 1) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return error;
}

int vas_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (vas_check_matrix_err(A) || vas_check_matrix_err(B) || result == NULL) {
    error = 1;
  }
  if (error < 1) {
    if (A->columns != B->rows) error = 2;
    if (error < 1) {
      if (vas_create_matrix(A->rows, B->columns, result) > 0) error = 1;
      if (error != 1) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    }
  }
  return error;
}

int vas_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (vas_check_matrix_err(A) || result == NULL) error = 1;
  if (error != 1) {
    if (vas_create_matrix(A->columns, A->rows, result) > 0) error = 1;
    if (error != 1) {
      result->rows = A->columns;
      result->columns = A->rows;
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return error;
}

int vas_eq_matrix(matrix_t *A, matrix_t *B) {
  int returnValue = SUCCESS;
  if (A == NULL && B == NULL) {
    returnValue = SUCCESS;
  } else if (A == NULL || B == NULL) {
    returnValue = FAILURE;
  } else {
    if (A->rows != B->rows || A->columns != B->columns) returnValue = FAILURE;
    if (returnValue != FAILURE) {
      for (int i = 0; i < A->rows; i++) {
        int forBreak = 0;
        for (int j = 0; j < A->columns && forBreak != 1; j++) {
          if (fabs(B->matrix[i][j] - A->matrix[i][j]) >= SEVEN_PRECISION) {
            forBreak = 1;
            returnValue = FAILURE;
          }
        }
      }
    }
  }
  return returnValue;
}

int vas_determinant(matrix_t *A, double *result) {
  int error = 0;
  double determinant = 0.0;
  if (vas_check_matrix_err(A) || result == NULL) error = 1;
  if (error < 1) {
    if ((A->rows != A->columns) || (A->rows < 1)) error = 2;
    if (error < 1) {
      if (A->rows == 1) {
        determinant = A->matrix[0][0];
      } else if (A->rows == 2) {
        determinant = (A->matrix[0][0] * A->matrix[1][1]) -
                      (A->matrix[0][1] * A->matrix[1][0]);
      } else if (A->rows == 3) {
        determinant = A->matrix[0][0] * (A->matrix[1][1] * A->matrix[2][2] -
                                         A->matrix[1][2] * A->matrix[2][1]) -
                      A->matrix[0][1] * (A->matrix[1][0] * A->matrix[2][2] -
                                         A->matrix[1][2] * A->matrix[2][0]) +
                      A->matrix[0][2] * (A->matrix[1][0] * A->matrix[2][1] -
                                         A->matrix[1][1] * A->matrix[2][0]);
      } else {
        int flip = -1;
        for (int i = 0; i < A->columns; i++) {
          matrix_t currentMinor;
          vas_get_minor(A, 0, i, &currentMinor);
          double minorDeterminant = 0.0;
          vas_determinant(&currentMinor, &minorDeterminant);
          flip = flip * -1;
          determinant += flip * A->matrix[0][i] * minorDeterminant;
          vas_remove_matrix(&currentMinor);
        }
      }
      *result = determinant;
    }
  }
  return error;
}

int vas_calc_complements(matrix_t *A,
                         matrix_t *result) {  // cofactor matrix
  int error = 0;
  if (vas_check_matrix_err(A) || result == NULL) error = 1;
  if (error < 1) {
    // if matrix is not of normal size, then size error:
    if (!(A->rows > 1 && A->rows == A->columns)) error = 2;
    if (error < 1) {
      vas_create_matrix(A->rows, A->columns, result);
      int flipI = 1;
      for (int i = 0; i < A->rows; i++) {
        int flipJ = 1;
        for (int j = 0; j < A->columns; j++) {
          matrix_t tempMatrix;
          double tempDeterminant = 0.0;
          vas_get_minor(A, i, j, &tempMatrix);
          vas_determinant(&tempMatrix, &tempDeterminant);
          result->matrix[i][j] = tempDeterminant * (flipI * flipJ);
          flipJ = flipJ * -1;
          vas_remove_matrix(&tempMatrix);
        }
        flipI = flipI * -1;
      }
    }
  }
  return error;
}

int vas_inverse_matrix(matrix_t *A, matrix_t *result) {
  double aDeterminant = 0.0;
  int error = 0;
  if (vas_check_matrix_err(A) || result == NULL || A->rows != A->columns) {
    error = 1;
  }
  if (error < 1) {
    vas_determinant(A, &aDeterminant);
    if (aDeterminant == 0) error = 2;
    if (error < 1) {
      if (A->rows == 1) {
        vas_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1 / aDeterminant;
      } else {
        matrix_t tempMatrix;
        matrix_t tempMatrixMultiplied;
        matrix_t tempMatrixTransposed;
        vas_create_matrix(A->rows, A->columns, result);
        vas_calc_complements(A, &tempMatrix);
        vas_mult_number(&tempMatrix, 1 / aDeterminant, &tempMatrixMultiplied);
        vas_transpose(&tempMatrixMultiplied, &tempMatrixTransposed);
        vas_copy_matrix(&tempMatrixTransposed, result);
        vas_remove_matrix(&tempMatrixTransposed);
        vas_remove_matrix(&tempMatrixMultiplied);
        vas_remove_matrix(&tempMatrix);
      }
    }
  }
  return error;
}

// HELPERS:
// --------

int vas_get_minor(matrix_t *A, int elimIdxI, int elimIdxJ, matrix_t *result) {
  int error = 0;
  if (A->rows < 2 || A->columns < 2) {
    error = 1;
  }
  if (error != 1) {
    vas_create_matrix(A->rows - 1, A->columns - 1, result);
    int k = 0;  // second matrix i idx
    if (error != 1) {
      for (int i = 0; i < A->rows; i++) {
        if (i != elimIdxI) {
          int h = 0;  // second matrix j idx
          for (int j = 0; j < A->columns; j++) {
            if (j != elimIdxJ) {
              result->matrix[k][h] = A->matrix[i][j];
              h++;
            }
          }
          k++;
        }
      }
    }
  }
  return error;
}

void vas_copy_matrix(matrix_t *from, matrix_t *to) {
  for (int i = 0; i < from->rows; i++) {
    for (int j = 0; j < from->columns; j++) {
      to->matrix[i][j] = from->matrix[i][j];
    }
  }
}

int vas_check_matrix_err(matrix_t *A) {
  int error = 0;
  if (A->rows < 1 || A->columns < 1 || A == NULL) error = 1;
  return error;
}

// FILLERS AND PRINTERS:
// --------

void vas_print_matrix(matrix_t A) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      printf("%10.4f", A.matrix[i][j]);
    }
    printf("\n");
  }
}

void vas_fill_matrix_random(matrix_t A, double scale) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = ((rand() % 200000) - 100000) * 0.0001 * scale;
    }
  }
}

void vas_fill_matrix_single(matrix_t A, double x) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = x;
    }
  }
}

void vas_fill_matrix_incr(matrix_t A, double x) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = x;
      x++;
    }
  }
}
