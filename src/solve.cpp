#include "solve.hpp"
#include "row_state.hpp"
#include "search.hpp"

std::vector<std::pair<int, int>> solve(int n, int m)
{
    RowState init{};
    for (int r = 0; r < n; ++r)
        init.rows[r] = static_cast<uint8_t>(m);
    for (int c = 0; c < m; ++c)
        init.cols[c] = static_cast<uint8_t>(n);
    init.height = n;
    init.width = m;
    if (n > m)
    {
        std::swap(init.rows, init.cols);
        std::swap(init.height, init.width);
    }

    std::vector<std::pair<int, int>> win;
    for (int i = 0; i < n; ++i)
    {
        int ri = init.rows[i];
        for (int j = ri - 1; j >= 0; --j)
        {
            if (i == 0 && j == 0)
                continue;
            RowState T = init;
            apply_move_and_canonicalize(T, i, j);
            if (!can_win(T))
                win.emplace_back(i, j);
        }
    }
    return win;
}
