#ifndef FERRERS_KEY_HPP
#define FERRERS_KEY_HPP

#include "config.hpp"

// Initialize binomial table
void init_binom();

// Encode a Ferrers diagram as a rank key
uint64_t make_key(const uint8_t *rows, uint8_t height);

#endif // FERRERS_KEY_HPP