#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "row_state.hpp"
#include <utility>
#include <cstdint>
#include <vector>

// Candidate move structure for search
struct Move
{
    uint16_t i, j, score;
    RowState next;
};

// Early termination checks: {done, result}
std::pair<bool, bool> early_judgment(RowState &S);

// Negamax + alpha-beta + memoized search
bool can_win(RowState &S);

#endif // SEARCH_HPP