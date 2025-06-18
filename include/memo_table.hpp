#ifndef MEMO_TABLE_HPP
#define MEMO_TABLE_HPP

#include "config.hpp"
#include <cstdint>
#include <string>

// Define uint128_t if not available
#if defined(__SIZEOF_INT128__)
typedef unsigned __int128 uint128_t;
#else
#error "Compiler does not support 128-bit integers (uint128_t)."
#endif

constexpr uint128_t n_choose_k(uint64_t n, uint64_t k)
{
    if (k > n)
        return 0;
    if (k > n - k)
        k = n - k; // 対称性を利用し、計算回数を減らす
    uint128_t result = 1;
    for (uint64_t i = 1; i <= k; ++i)
    {
        result = result * (n - i + 1) / i;
    }
    return result;
}

static constexpr uint128_t COMBINATION_COUNT = n_choose_k(N_GRID_SIZE + M_GRID_SIZE, M_GRID_SIZE);
static constexpr uint8_t STATE_BITS = 2;
static constexpr uint128_t MEMO_BITS = COMBINATION_COUNT * STATE_BITS;
static constexpr uint128_t MEMO_BYTES = (MEMO_BITS + 7) / 8;

extern uint8_t *memo;

uint8_t get_state(uint128_t key);
void set_state(uint128_t key, uint8_t v);
void load_memo(const std::string &path);
void save_memo(const std::string &path);
std::string memo_filename();

#endif // MEMO_TABLE_HPP