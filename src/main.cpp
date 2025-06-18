#include "config.hpp"
#include <iostream>
#include <cstring>
#include "ferrers_key.hpp"
#include "memo_table.hpp"
#include "solve.hpp"

int main()
{
    std::cout << "Estimated memory usage: " << static_cast<std::size_t>(MEMO_BYTES) / 1024 << " KB" << std::endl;
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();
    std::cout << "Starting computation..." << std::endl;
    std::cout << "N_SEARCH_MAX: " << N_SEARCH_MAX << ", M_SEARCH_MAX: " << M_SEARCH_MAX << std::endl;
    std::cout << "N_GRID_SIZE: " << N_GRID_SIZE << ", M_GRID_SIZE: " << M_GRID_SIZE << std::endl;

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