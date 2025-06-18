#include "config.hpp"
#include <iostream>
#include <cstring>
#include "ferrers_key.hpp"
#include "memo_table.hpp"
#include "solve.hpp"

int main()
{
    init_binom();

    memo = (uint8_t *)std::aligned_alloc(4096, MEMO_BYTES);
    std::memset(memo, 0, MEMO_BYTES);
    load_memo(memo_filename());

    for (int n = 1; n <= N_SEARCH_MAX; ++n)
    {
        for (int m = 1; m <= M_SEARCH_MAX; ++m)
        {
            auto ws = solve(n, m);
            std::cout << "n=" << n << ", m=" << m << ": ";
            for (auto &p : ws)
                std::cout << '(' << p.first << ", " << p.second << ") ";
            std::cout << std::endl;
        }
    }

    save_memo(memo_filename());
    return 0;
}