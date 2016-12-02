/*
    Doolittle's Method LU factorization.
    for column major matrix.
 */
#pragma once

int column_major_index(int N, int row, int column);
bool doolittle_lu_decomposition(int N, float* A, int* pivot, int* num_inversions);
void doolittle_lu_forward_substitution(int N, const float* LU, const int* pivot, const float* b, float* y);
void doolittle_lu_backward_substitution(int N, const float* LU, const float* y, float* x);
void doolittle_lu_solve(int N, const float* LU, const int* pivot, const float* b, float* x);