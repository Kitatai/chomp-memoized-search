#include "search.hpp"
#include "memo_table.hpp"
#include <vector>
#include <algorithm>

std::pair<bool, bool> early_judgment(RowState &S)
{
    if (S.height == 1 && S.width == 1)
        return {true, false};

    if (S.height == 1 || S.width == 1)
        return {true, true};

    if (S.height == S.width)
        return {true, S.rows[1] > 1};

    if (S.rows[0] - S.rows[1] == 1)
        return {true, S.cols[0] > 2};
    if (S.cols[0] - S.cols[1] == 1)
        return {true, S.rows[0] > 2};

    if (S.rows[S.height - 1] == S.width || S.cols[S.rows[S.height - 1]] == 0)
        return {true, true};

    return {false, true};
}

bool can_win(RowState &S)
{
    std::pair<bool, bool> judgment_result = early_judgment(S);
    if (judgment_result.first)
        return judgment_result.second;

    uint128_t k = S.key();
    // 自局面メモ参照
    uint8_t st = get_state(k);
    if (st != 0)
        return (st == 1);

    // 候補手列挙
    std::vector<Move> cand;
    cand.reserve(S.height * S.width);

    std::vector<std::vector<uint16_t>> removed(S.height + 1, std::vector<uint16_t>(S.width + 1, 0));

    for (int i = S.height - 1; i >= 0; --i)
    {
        uint16_t ri = S.rows[i];
        for (int j = ri - 1; j >= 0; --j)
        {
            if (i == 0 && j == 0)
                continue;

            // 子ノードのメモ参照で “1手で証明済み勝ち” を優先
            RowState child = S;
            apply_move_and_canonicalize(child, i, j);
            uint128_t kc = child.key();
            uint8_t st = get_state(kc);
            if (st == 2)
            {
                set_state(k, 1);
                return true;
            }

            // 切り取ったマスの数をdpで計算
            removed[i][j] = 1 + removed[i + 1][j] + removed[i][j + 1] - removed[i + 1][j + 1];

            cand.push_back({static_cast<uint16_t>(i), static_cast<uint16_t>(j), removed[i][j], child});
        }
    }

    // 切り取ったマスが多い順にソート
    std::sort(cand.begin(), cand.end(),
              [](const Move &a, const Move &b)
              { return a.score > b.score; });

    // 論理的に勝てる手を探索
    for (auto &mv : cand)
    {
        if (!can_win(mv.next))
        {
            set_state(k, 1);
            return true;
        }
    }
    set_state(k, 2);
    return false;
}