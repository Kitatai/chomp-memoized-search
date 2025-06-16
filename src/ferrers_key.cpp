#include "ferrers_key.hpp"
#include <algorithm>

static uint64_t binom[2 * GRID_SIZE][GRID_SIZE + 1];

void init_binom()
{
    for (int n = 0; n < 2 * GRID_SIZE; ++n)
    {
        binom[n][0] = 1;
        for (int k = 1; k <= std::min(n, (int)GRID_SIZE); ++k)
        {
            if (k == n)
                binom[n][k] = 1;
            else
                binom[n][k] = binom[n - 1][k - 1] + binom[n - 1][k];
        }
    }
}

uint64_t make_key(const uint8_t *rows, uint8_t height)
{
    const int L = 2 * GRID_SIZE - 1;
    int remT = L;
    int remR = GRID_SIZE;

    uint64_t rank = 0;

    for (int i = 0; i < (GRID_SIZE - rows[0]); ++i)
    {
        --remT;
        rank += binom[remT][remR];
        --remR;
    }
    --remT;

    for (int r = 1; r < height; ++r)
    {
        int rights = rows[r - 1] - rows[r];
        for (int i = 0; i < rights; ++i)
        {
            --remT;
            rank += binom[remT][remR];
            --remR;
        }
        --remT;
    }

    for (int i = 0; i < rows[height - 1]; ++i)
    {
        --remT;
        rank += binom[remT][remR];
        --remR;
    }

    return rank;
}