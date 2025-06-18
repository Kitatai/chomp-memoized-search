#ifndef FERRERS_KEY_HPP
#define FERRERS_KEY_HPP

#include "config.hpp"
#include "row_state.hpp"

// Define uint128_t if not available
#if defined(__SIZEOF_INT128__)
typedef unsigned __int128 uint128_t;
#else
#error "Compiler does not support 128-bit integers (uint128_t)."
#endif

// Initialize binomial table
void init_binom();

// Encode a Ferrers diagram as a rank key
uint128_t make_key(const RowState &S);

#endif // FERRERS_KEY_HPP