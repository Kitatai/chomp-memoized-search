#include "solve.hpp"
#include "row_state.hpp"
#include "search.hpp"

std::vector<std::pair<int, int>> solve_internal(int n_small, int m_small)
{
    RowState init{};
    for (int r = 0; r < n_small; ++r)
        init.rows[r] = static_cast<uint8_t>(m_small);
    for (int c = 0; c < m_small; ++c)
        init.cols[c] = static_cast<uint8_t>(n_small);
    init.height = n_small;
    init.width = m_small;
    if (n_small > m_small)
    {
        std::swap(init.rows, init.cols); // ポインタだけ交換
        std::swap(init.height, init.width);
    }

    std::vector<std::pair<int, int>> win;
    for (int i = 0; i < n_small; ++i)
    {
        int ri = init.rows[i];
        for (int j = ri - 1; j >= 0; --j)
        {
            if (i == 0 && j == 0)
                continue;
            RowState T = init;
            apply_move_and_canonicalize(T, i, j);
            if (!can_win(T, n_small, m_small))
                win.emplace_back(i, j);
        }
    }
    return win;
}

std::vector<std::pair<int, int>> solve_wrapper(int n, int m)
{
    if (n > m)
    {
        auto res = solve_internal(m, n);
        for (auto &p : res)
            std::swap(p.first, p.second);
        return res;
    }
    return solve_internal(n, m);
}