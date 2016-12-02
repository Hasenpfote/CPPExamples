/*
    Crout's Method LU factorization.
    for row major matrix.
 */
#pragma once

int row_major_index(int N, int row, int column);
bool crout_lu_decomposition(int N, float* A, int* pivot, int* num_inversions);
void crout_lu_forward_substitution(int N, const float* LU, const int* pivot, const float* b, float* y);
void crout_lu_backward_substitution(int N, const float* LU, const float* y, float* x);
void crout_lu_solve(int N, const float* LU, const int* pivot, const float* b, float* x);