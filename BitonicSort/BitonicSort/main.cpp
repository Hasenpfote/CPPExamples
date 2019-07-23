#include <iostream>
#include <cstdlib>
#include <cassert>
#include <array>
#include <cmath>
#include <vector>
#include <numeric>
#include <random>

int solve_quadratic_equation(double a, double b, double c, std::array<double, 2> & roots)
{
    double d = b * b - 4.0 * a * c;
    if(d < 0.0)
        return 0;   // equation has imaginary roots.

    double x = (std::abs(b) + std::sqrt(d)) / (2.0 * a);
    if(d > 0.0)
    {
        // equation has 2 roots.
        if(b < 0.0) // negative sign
        {
            // x1 = (- b - ãD) / 2a = (- (-|b|) - ãD) / 2a = (|b| - ãD) / 2a ... When b is larger, There is a possibility to underflow.
            // x2 = (- b + ãD) / 2a = (- (-|b|) + ãD) / 2a = (|b| + ãD) / 2a
            roots[0] = c / (a * x);	// rationalize the numerator
            roots[1] = x;
        }
        else        // positive sign
        {
            // x1 = (- b - ãD) / 2a = (- (+|b|) - ãD) / 2a = (-|b| - ãD) / 2a = -(|b| + ãD) / 2a
            // x2 = (- b + ãD) / 2a = (- (+|b|) + ãD) / 2a = (-|b| + ãD) / 2a = -(|b| - ãD) / 2a ... When b is larger, There is a possibility to underflow.
            roots[0] = -x;
            roots[1] = -(c / (a * x));	// rationalize the numerator
        }
        return 2;
    }

    // equation has 1 root
    roots[0] = roots[1] = (b < 0.0) ? x : -x;
    return 1;
}

double next_power_of_2(double x)
{
    return std::pow(2.0, std::ceil(std::log2(x)));
}

int pass_to_step(int pass)
{
    // ax^2 + bx + c = 0
    double a = 1.0;
    double b = 1.0;
    double c = -2.0 * static_cast<double>(pass);
    std::array<double, 2> roots;
    auto ret = solve_quadratic_equation(a, b, c, roots);
    assert(ret > 0);
    auto root = std::max(roots[0], roots[1]);

    return static_cast<int>(std::ceil(root));
}

int pass_to_stage(int pass, int step)
{
    auto sum = step * (step + 1) / 2;
    return sum - pass + 1;
}

int stage_to_offset(int stage)
{
    return std::pow(2.0, stage - 1);
}

std::vector<int> random_vector(int size)
{
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 0);

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(v.begin(), v.end(), engine);

    return v;
}

int main()
{
    auto N = static_cast<int>(std::pow(2.0, 5.0));
    assert(N == static_cast<int>(next_power_of_2(N)));

    auto v = random_vector(N);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    auto n = static_cast<int>(std::log2(N));
    auto num_passes = n * (n + 1) / 2;

    for(decltype(num_passes) pass = 1; pass <= num_passes; pass++)
    {
        auto step = pass_to_step(pass);
        auto stage = pass_to_stage(pass, step);
        auto seq_size = static_cast<int>(std::pow(2.0, step));
        auto offset = stage_to_offset(stage);
        auto range = offset * 2;

        std::cout
            << "pass=" << pass
            << " step:" << step
            << " stage:" << stage
            << " seq_size:" << seq_size
            << " offset:" << offset
            << std::endl;

        // Emulate a GPU processing.
        for(decltype(N) i = 0; i < N; i++)
        {
            auto texel = i + 0.5;
            auto fetch_dir = (std::fmod(texel, range) < offset) ? 1 : -1;
            auto f = std::floor(texel / seq_size);
            auto sort_dir = (std::fmod(f, 2.0) <= 0.5) ? 1 : -1;

            auto j = fetch_dir * offset + i;

            if(sort_dir == 1)
            {
                if(fetch_dir == 1)
                {
                    if(v[i] > v[j])
                        std::swap(v[i], v[j]);
                }
            }
            else
            {
                if(fetch_dir == 1)
                {
                    if(v[i] < v[j])
                        std::swap(v[i], v[j]);
                }
            }
        }
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    std::cout << std::endl;
}