#include <utility>
#include <cmath>
#include "crout.h"

int row_major_index(int N, int row, int column)
{
    return row * N + column;
}

bool crout_lu_decomposition(int N, float* A, int* pivot, int* num_inversions)
{
    for(auto i = 0; i < N; i++)
        pivot[i] = i;
    *num_inversions = 0;

    for(int k = 0; k < N; k++){ // row & column
        int p = k;
        for(auto i = k + 1; i < N; i++){    // row
            auto ik = row_major_index(N, i, k);
            auto pk = row_major_index(N, p, k);
            if(std::abs(A[ik]) > std::abs((A[pk]))){
                p = i;
            }
        }

        if(p != k){
            for(auto j = 0; j < N; j++){    // column
                auto pj = row_major_index(N, p, j);
                auto kj = row_major_index(N, k, j);
                std::swap(A[pj], A[kj]);
            }
            std::swap(pivot[p], pivot[k]);
            (*num_inversions)++;
        }

        auto kk = row_major_index(N, k, k);
        if(A[kk] == 0.0)    // The matrix is singular.
            return false;

        for(int i = k + 1; i < N; i++){ // row
            auto ki = row_major_index(N, k, i);
            A[ki] /= A[kk];
        }
        for(int i = k + 1; i < N; i++){ // row
            auto ik = row_major_index(N, i, k);
            for(int j = k + 1; j < N; j++){ // column
                auto ij = row_major_index(N, i, j);
                auto kj = row_major_index(N, k, j);
                A[ij] -= A[kj] * A[ik];
            }
        }
    }
    return true;
}

/*
    e.g.
    N = 4
    | l00  0    0    0  |   | y0 |   | b0 |
    | l10  l11  0    0  | * | y1 | = | b1 |
    | l20  l21  l22  0  |   | y2 |   | b2 |
    | l30  l31  l32  l33|   | y3 |   | b3 |

    y0 = b0 / l00
    y1 = (b1 - l10y0) / l11
    y2 = (b2 - l20y0 - l21y1) / l22
    y3 = (b3 - l30y0 - l31y1 - l32y2) /l33
 */
void crout_lu_forward_substitution(int N, const float* LU, const int* pivot, const float* b, float* y)
{
    // TODO: b は予め pivoting しておくとメモリ効率がいい
    y[0] = b[pivot[0]] / LU[row_major_index(N, 0, 0)];
    for(auto k = 1; k < N; k++){        // row & column
        y[k] = b[pivot[k]];
        for(auto i = 0; i < k; i++){    // column
            auto index = row_major_index(N, k, i);
            y[k] -= LU[index] * y[i];
        }
        y[k] /= LU[row_major_index(N, k, k)];
    }
}

/*
    e.g.
    N=4
    |1   u01  u02  u03|   |x0|   |y0|
    |0   1    u12  u13| * |x1| = |y1|
    |0   0    1    u23|   |x2|   |y2|
    |0   0    0    1  |   |x3|   |y3|

    x3 = y3
    x2 = y2 - u23x3
    x1 = y1 - u12x2 - u13x3
    x0 = y0 - u01x1 - u02x2 - u03x3
 */
void crout_lu_backward_substitution(int N, const float* LU, const float* y, float* x)
{
    x[N-1] = y[N-1];
    for(auto k = N - 2; k >= 0; k--){       // row & column
        x[k] = y[k];
        for(auto i = k + 1; i < N; i++){    // column
            auto index = row_major_index(N, k, i);
            x[k] -= LU[index] * x[i];
        }
    }
}

void crout_lu_solve(int N, const float* LU, const int* pivot, const float* b, float* x)
{
    // forward substitution.
    x[0] = b[pivot[0]] / LU[row_major_index(N, 0, 0)];
    for(auto k = 1; k < N; k++){        // row & column
        x[k] = b[pivot[k]];
        for(auto i = 0; i < k; i++){    // column
            auto index = row_major_index(N, k, i);
            x[k] -= LU[index] * x[i];
        }
        x[k] /= LU[row_major_index(N, k, k)];
    }
    // backward substitution.
    for(auto k = N - 2; k >= 0; k--){       // row & column
        for(auto i = k + 1; i < N; i++){    // column
            auto index = row_major_index(N, k, i);
            x[k] -= LU[index] * x[i];
        }
    }
}