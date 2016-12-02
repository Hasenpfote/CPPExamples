#include <iostream>
#include <cmath>
#include <cassert>
#include "doolittle.h"
#include "crout.h"

const int N = 3;

void print_array1d(const float a[N])
{
    std::cout << a[0];
    for(int i = 1; i < N; i++)
        std::cout << ", " << a[i];
    std::cout << std::endl;
}

void print_array2d(const float a[][N])
{
    for(int i = 0; i < N; i++){
        std::cout << a[i][0];
        for(int j = 1; j < N; j++){
            std::cout << ", "<< a[i][j];
        }
        std::cout << std::endl;
    }
}

void mult(const float lhs[][N], const float rhs[][N], float m[][N])
{
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            float elem = 0;
            for(int k = 0; k < N; k++){
                elem += lhs[i][k] * rhs[k][j];
            }
            m[i][j] = elem;
        }
    }
}

void permutation_matrix(const int pivot[N], float m[][N])
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            m[i][j] = (j == pivot[i]) ? 1.0f : 0.0f;
}

// Doolittle's Method LU factorization.(column major)
void test_doolittle(const float A[][N])
{
    std::cout << "*** Doolittle's Method LU factorization. ***" << std::endl;
    float lu[N*N];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            lu[column_major_index(N, i, j)] = A[i][j];

    int pivot[N];
    int num_inversions;
    auto ret = doolittle_lu_decomposition(N, lu, pivot, &num_inversions);
    std::cout << std::boolalpha << "Is singular? " << !ret << std::endl;
    if(!ret)
        return;
    // PA = LU
    {
        std::cout << "(1) PA = LU" << std::endl;
        std::cout << "LU =" << std::endl;
        // Lower triangular matrix.
        float L[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++){
                if(j < i){ L[i][j] = lu[column_major_index(N, i, j)]; }
                else if(j == i){ L[i][j] = 1.0f; }
                else{ L[i][j] = 0.0f; }
            }
        // Upper triangular matrix.
        float U[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                U[i][j] = (j >= i) ? lu[column_major_index(N, i, j)] : 0.0f;

        float LU[N][N];
        mult(L, U, LU);
        print_array2d(LU);
        std::cout << std::endl;

        std::cout << "PA =" << std::endl;
        float P[N][N];
        permutation_matrix(pivot, P);
        float PA[N][N];
        mult(P, A, PA);
        print_array2d(PA);
        std::cout << std::endl;
    }
    // Ax = b
    {
        std::cout << "(2) Ax = b" << std::endl;
        std::cout << "b = ";
        float b[N];
        for(int i = 0; i < N; i++)
            b[i] = (i == 0) ? 1.0f : 0.0f;
        print_array1d(b);

        std::cout << "x = ";
        float y[N], x[N];
        doolittle_lu_forward_substitution(N, lu, pivot, b, y);
        doolittle_lu_backward_substitution(N, lu, y, x);
        doolittle_lu_solve(N, lu, pivot, b, x);
        print_array1d(x);
        std::cout << std::endl;
    }
    // Determinant
    {
        std::cout << "(3) det|A|" << std::endl;
        float prod = lu[column_major_index(N, 0, 0)];
        for(int i = 1; i < N; i++)
            prod *= lu[column_major_index(N, i, i)];
        float sign = (num_inversions % 2) ? -1.0f : 1.0f;
        float det = sign * prod;
        std::cout << "det = " << det << std::endl;
        std::cout << std::endl;
    }
    // AX = E
    {
        std::cout << "(4) AX = E" << std::endl;
        float x[N];
        float b[N];
        std::cout << "X =" << std::endl;
        float X[N][N];
        for(int i = 0; i < N; i++){
            for(int k = 0; k < N; k++)
                b[k] = (k == i) ? 1.0f : 0.0f;
            doolittle_lu_solve(N, lu, pivot, b, x);
            for(int j = 0; j < N; j++){
                X[j][i] = x[j];
            }
        }
        print_array2d(X);
        std::cout << std::endl;

        std::cout << "AX =" << std::endl;
        float AX[N][N];
        mult(A, X, AX);
        print_array2d(AX);
        std::cout << std::endl;
    }
}

// Crout's Method LU factorization.(row major)
void test_crout(const float A[][N])
{
    std::cout << "*** Crout's Method LU factorization. ***" << std::endl;
    float lu[N*N];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            lu[row_major_index(N, i, j)] = A[i][j];

    int pivot[N];
    int num_inversions;
    auto ret = crout_lu_decomposition(N, lu, pivot, &num_inversions);
    std::cout << std::boolalpha << "Is singular? " << !ret << std::endl;
    if(!ret)
        return;
    // PA = LU
    {
        std::cout << "(1) PA = LU" << std::endl;
        std::cout << "LU =" << std::endl;
        // Lower triangular matrix.
        float L[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++){
                L[i][j] = (j <= i) ? lu[row_major_index(N, i, j)] : 0.0f;
            }
        // Upper triangular matrix.
        float U[N][N];
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++){
                if(j > i){ U[i][j] = lu[row_major_index(N, i, j)]; }
                else if(j == i){ U[i][j] = 1.0f; }
                else{ U[i][j] = 0.0f; }
            }

        float LU[N][N];
        mult(L, U, LU);
        print_array2d(LU);
        std::cout << std::endl;

        std::cout << "PA =" << std::endl;
        float P[N][N];
        permutation_matrix(pivot, P);
        float PA[N][N];
        mult(P, A, PA);
        print_array2d(PA);
        std::cout << std::endl;
    }
    // Ax = b
    {
        std::cout << "(2) Ax = b" << std::endl;
        std::cout << "b = ";
        float b[N];
        for(int i = 0; i < N; i++)
            b[i] = (i == 0) ? 1.0f : 0.0f;
        print_array1d(b);

        std::cout << "x = ";
        float y[N], x[N];
        crout_lu_forward_substitution(N, lu, pivot, b, y);
        crout_lu_backward_substitution(N, lu, y, x);
        crout_lu_solve(N, lu, pivot, b, x);
        print_array1d(x);
        std::cout << std::endl;
    }
    // Determinant
    {
        std::cout << "(3) det|A|" << std::endl;
        float prod = lu[row_major_index(N, 0, 0)];
        for(int i = 1; i < N; i++)
            prod *= lu[row_major_index(N, i, i)];
        float sign = (num_inversions % 2) ? -1.0f : 1.0f;
        float det = sign * prod;
        std::cout << "det = " << det << std::endl;
        std::cout << std::endl;
    }
    // AX = E
    {
        std::cout << "(4) AX = E" << std::endl;
        float x[N];
        float b[N];
        std::cout << "X =" << std::endl;
        float X[N][N];
        for(int i = 0; i < N; i++){
            for(int k = 0; k < N; k++)
                b[k] = (k == i) ? 1.0f : 0.0f;
            crout_lu_solve(N, lu, pivot, b, x);
            for(int j = 0; j < N; j++){
                X[j][i] = x[j];
            }
        }
        print_array2d(X);
        std::cout << std::endl;

        std::cout << "AX =" << std::endl;
        float AX[N][N];
        mult(A, X, AX);
        print_array2d(AX);
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    const float A[N][N] = {
        { 2.0f, 2.0f, 2.0f },
        { 1.0f, 3.0f, 1.0f },
        { 3.0f, 1.0f, 4.0f }
    };
    // Doolittle's Method LU factorization.(column major)
    test_doolittle(A);

    // Crout's Method LU factorization.(row major)
    test_crout(A);
}