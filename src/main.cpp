#include "config.hpp"
#include <iostream>
#include <cstring>
#include "ferrers_key.hpp"
#include "memo_table.hpp"
#include "solve.hpp"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init_binom();

    memo = (uint8_t *)std::aligned_alloc(4096, MEMO_BYTES);
    std::memset(memo, 0, MEMO_BYTES);
    load_memo("memo.bin");

    for (int n = 1; n <= N_MAX; ++n)
    {
        for (int m = 1; m <= M_MAX; ++m)
        {
            auto ws = solve_wrapper(n, m);
            std::cout << "n=" << n << ", m=" << m << ": ";
            for (auto &p : ws)
                std::cout << '(' << p.first << ", " << p.second << ") ";
            std::cout << std::endl;
        }
    }

    save_memo("memo.bin");
    return 0;
}