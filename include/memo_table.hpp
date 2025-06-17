#ifndef MEMO_TABLE_HPP
#define MEMO_TABLE_HPP

#include "config.hpp"
#include <cstdint>
#include <string>

constexpr uint64_t n_choose_k(uint64_t n, uint64_t k)
{
    if (k > n)
        return 0;
    if (k > n - k)
        k = n - k; // 対称性を利用し、計算回数を減らす
    uint64_t result = 1;
    for (uint64_t i = 1; i <= k; ++i)
    {
        result = result * (n - i + 1) / i;
    }
    return result;
}

static constexpr uint64_t COMBINATION_COUNT = n_choose_k(2 * GRID_SIZE - 1, GRID_SIZE);
static constexpr uint8_t STATE_BITS = 2;
static constexpr uint64_t MEMO_BITS = COMBINATION_COUNT * STATE_BITS;
static constexpr uint64_t MEMO_BYTES = (MEMO_BITS + 7) / 8;

extern uint8_t *memo;

uint8_t get_state(uint64_t key);
void set_state(uint64_t key, uint8_t v);
void load_memo(const std::string &path);
void save_memo(const std::string &path);

#endif // MEMO_TABLE_HPP