#ifndef ROW_STATE_HPP
#define ROW_STATE_HPP

#include "config.hpp"
#include <array>
#include <cstdint>

struct RowState
{
    std::array<uint8_t, GRID_SIZE + 1> bufA, bufB;
    uint8_t *rows;
    uint8_t *cols;
    uint8_t height, width;
    RowState();
    RowState(const RowState &);
    RowState &operator=(const RowState &);
    uint64_t key() const;
};

// Apply move and normalize (including transpose)
void apply_move_and_canonicalize(RowState &S, int i, int j);

#endif // ROW_STATE_HPP