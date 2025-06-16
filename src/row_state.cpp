#include "row_state.hpp"
#include "ferrers_key.hpp"
#include <algorithm>

RowState::RowState()
{
    rows = bufA.data();
    cols = bufB.data();
    height = width = 0;
}

RowState::RowState(const RowState &o)
    : bufA(o.bufA), bufB(o.bufB),
      height(o.height), width(o.width)
{
    bool rowsIsA = (o.rows == o.bufA.data());
    rows = rowsIsA ? bufA.data() : bufB.data();
    cols = rowsIsA ? bufB.data() : bufA.data();
}

RowState &RowState::operator=(const RowState &o)
{
    if (this == &o)
        return *this;
    bufA = o.bufA;
    bufB = o.bufB;
    height = o.height;
    width = o.width;
    bool rowsIsA = (o.rows == o.bufA.data());
    rows = rowsIsA ? bufA.data() : bufB.data();
    cols = rowsIsA ? bufB.data() : bufA.data();
    return *this;
}

uint64_t RowState::key() const
{
    return make_key(rows, height);
}

void apply_move_and_canonicalize(RowState &S, int i, int j)
{
    // 行、列更新
    for (int r = i; r < S.height; ++r)
    {
        if (S.rows[r] <= j)
            break;
        S.rows[r] = static_cast<uint8_t>(j);
    }
    for (int c = j; c < S.width; ++c)
    {
        if (S.cols[c] <= i)
            break;
        S.cols[c] = static_cast<uint8_t>(i);
    }
    // 幅を更新
    S.width = S.rows[0];
    S.height = S.cols[0];

    // 必要なら転置
    if (S.height > S.width)
    {
        std::swap(S.rows, S.cols);
        std::swap(S.height, S.width);
    }
}