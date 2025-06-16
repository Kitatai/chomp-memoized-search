#ifndef MEMO_TABLE_HPP
#define MEMO_TABLE_HPP

#include "config.hpp"
#include <cstdint>
#include <string>

static constexpr uint64_t NUM_KEYS = 1ULL << KEY_BITS;
static constexpr uint8_t STATE_BITS = 2;
static constexpr uint64_t MEMO_BITS = NUM_KEYS * STATE_BITS;
static constexpr uint64_t MEMO_BYTES = (MEMO_BITS + 7) / 8;

extern uint8_t *memo;

uint8_t get_state(uint64_t key);
void set_state(uint64_t key, uint8_t v);
void load_memo(const std::string &path);
void save_memo(const std::string &path);

#endif // MEMO_TABLE_HPP