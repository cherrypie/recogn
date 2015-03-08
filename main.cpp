#include "task1.hpp"

#define N 20

solver buildSumDistribution(int n)
{
    solver s(n, n * 9 + 1);

    object iv(n * 9 + 1);
    for(size_t i = 0; i < 10; ++i)
        iv.labels[i].weight = 0.1;

    s.setInitObject(&iv);

    for(int i = 1; i < n; ++i)
        for(int sum = 0; sum <= (i + 1) * 9; ++sum)
            for(int j = sum; j >= 0 && j >= sum - 9; --j)
                s.setEdge(0.1, i - 1, j, i, sum);

    s.solvePlus();

    return s;
}

int main()
{
    solver sum = buildSumDistribution(N);

    for(int i = 0; i <= N * 9; ++i)
        std::cout << i << " " << sum.getWeight(N - 1, i) << std::scientific << std::endl;

    std::cout << "\nThe most possible sum is " << sum.getMaxPlus(N - 1) << std::endl;

    return 0;
}
