#include <utility>
#include <cmath>
#include "doolittle.h"

int column_major_index(int N, int row, int column)
{
    return column * N + row;
}

bool doolittle_lu_decomposition(int N, float* A, int* pivot, int* num_inversions)
{
    for(auto i = 0; i < N; i++)
        pivot[i] = i;
    *num_inversions = 0;

    for(int k = 0; k < N; k++){ // row & column
        int p = k;
        for(auto i = k + 1; i < N; i++){    // row
            auto ik = column_major_index(N, i, k);
            auto pk = column_major_index(N, p, k);
            if(std::abs(A[ik]) > std::abs((A[pk]))){
                p = i;
            }
        }

        if(p != k){
            for (auto j = 0; j < N; j++) {    // column
                auto pj = column_major_index(N, p, j);
                auto kj = column_major_index(N, k, j);
                std::swap(A[pj], A[kj]);
            }
            std::swap(pivot[p], pivot[k]);
            (*num_inversions)++;
        }

        auto kk = column_major_index(N, k, k);
        if(A[kk] == 0.0)    // The matrix is singular.
            return false;

        for(int i = k + 1; i < N; i++){ // row
            auto ik = column_major_index(N, i, k);
            A[ik] /= A[kk];
        }
        for(int i = k + 1; i < N; i++){ // column
            auto ki = column_major_index(N, k, i);
            for(int j = k + 1; j < N; j++){ // row
                auto ji = column_major_index(N, j, i);
                auto jk = column_major_index(N, j, k);
                A[ji] -= A[jk] * A[ki];
            }
        }
    }
    return true;
}

/*
    e.g.
    N=4
        |1    0    0    0|   |y0|   |b0|
        |l10  1    0    0| * |y1| = |b1|
        |l20  l21  1    0|   |y2|   |b2|
        |l30  l31  l32  1|   |y3|   |b3|

        y0 = b0
        y1 = b1 - l10y0
        y2 = b2 - l20y0 - l21y1
        y3 = b3 - l30y0 - l31y1 - l32y2
 */
void doolittle_lu_forward_substitution(int N, const float* LU, const int* pivot, const float* b, float* y)
{
    // TODO: b は予め pivoting しておくとメモリ効率がいい
    for(auto k = 0; k < N; k++)
        y[k] = b[pivot[k]];

    for(auto k = 1; k < N; k++){        // row & column
        for(auto i = k; i < N; i++){    // row
            auto index = column_major_index(N, i, k-1);
            y[i] -= LU[index] * y[k-1];
        }
    }
}

/*
    e.g.
    N=4
        |u00  u01  u02  u03|   |x0|   |y0|
        |0    u11  u12  u13| * |x1| = |y1|
        |0    0    u22  u23|   |x2|   |y2|
        |0    0    0    u33|   |x3|   |y3|

        x3 = y3 / u33
        x2 = (y2                 - u23x3) / u22
        x1 = (y1         - u12x2 - u13x3) / u11
        x0 = (y0 - u01x1 - u02x2 - u03x3) / u00
 */
void doolittle_lu_backward_substitution(int N, const float* LU, const float* y, float* x)
{
    for(auto k = 0; k < N; k++)
        x[k] = y[k];

    x[N-1] /= LU[column_major_index(N, N-1, N-1)];
    for(auto k = N - 2; k >= 0; k--){   // row & column
        for(auto i = k; i >= 0; i--){   // row
            auto index = column_major_index(N, i, k+1);
            x[i] -= LU[index] * x[k+1];
        }
        x[k] /= LU[column_major_index(N, k, k)];
    }
}

void doolittle_lu_solve(int N, const float* LU, const int* pivot, const float* b, float* x)
{
    for(auto k = 0; k < N; k++)
        x[k] = b[pivot[k]];
    // forward substitution.
    for(auto k = 1; k < N; k++){        // row & column
        for(auto i = k; i < N; i++){    // row
            auto index = column_major_index(N, i, k - 1);
            x[i] -= LU[index] * x[k - 1];
        }
    }
    // backward substitution.
    x[N - 1] /= LU[column_major_index(N, N - 1, N - 1)];
    for(auto k = N - 2; k >= 0; k--){   // row & column
        for(auto i = k; i >= 0; i--){   // row
            auto index = column_major_index(N, i, k + 1);
            x[i] -= LU[index] * x[k + 1];
        }
        x[k] /= LU[column_major_index(N, k, k)];
    }
}