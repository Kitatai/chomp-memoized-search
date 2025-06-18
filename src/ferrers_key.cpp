#include "ferrers_key.hpp"
#include <algorithm>
#include "memo_table.hpp"
#include "row_state.hpp"

static uint64_t binom[N_GRID_SIZE + M_GRID_SIZE + 1][M_GRID_SIZE + 1];

void init_binom()
{
    const int size1 = N_GRID_SIZE + M_GRID_SIZE + 1;
    for (int n = 0; n < size1; ++n)
    {
        binom[n][0] = 1;
        for (int k = 1; k <= std::min(n, int(M_GRID_SIZE)); ++k)
        {
            if (k == n)
                binom[n][k] = 1;
            else
                binom[n][k] = binom[n - 1][k - 1] + binom[n - 1][k];
        }
    }
}

uint128_t make_key_sub(const uint8_t *rows, uint8_t height)
{
    // 定数 L はエンコード盤面の全体長：ENCODING_N_GRID_SIZE + ENCODING_M_GRID_SIZE
    const int L = N_GRID_SIZE + M_GRID_SIZE;
    int remT = L;
    // remR は選択すべきセルの数で、デフォルトはエンコード盤面の高さ
    int remR = M_GRID_SIZE;

    uint128_t rank = 0;

    // 初期状態: 盤面上部の余白分を処理
    for (int i = 0; i < (M_GRID_SIZE - rows[0]); ++i)
    {
        --remT;
        rank += binom[remT][remR];
        --remR;
    }
    --remT;

    // 各行で、前の行との差分（右側に切り取られたマス数）を加味する
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

    // 最終行の処理: 最後の行で残っているマスを処理
    for (int i = 0; i < rows[height - 1]; ++i)
    {
        --remT;
        rank += binom[remT][remR];
        --remR;
    }

    return rank;
}

uint128_t make_key(const RowState &S)
{
    if (S.bufA.data()[0] > S.bufB.data()[0])
        return make_key_sub(S.bufA.data(), S.bufB.data()[0]);
    else
        return make_key_sub(S.bufB.data(), S.bufA.data()[0]);
}