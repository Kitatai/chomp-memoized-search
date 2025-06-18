#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdint>

static constexpr int N_SEARCH_MAX = 11;
static constexpr int M_SEARCH_MAX = 20;
static constexpr int N_GRID_SIZE = 11;
static constexpr int M_GRID_SIZE = 20;

// N_SEARCH_MAX は N_GRID_SIZE以下でなければならない
static_assert(N_SEARCH_MAX <= N_GRID_SIZE, "N_SEARCH_MAX must be less than or equal to N_GRID_SIZE");
// M_SEARCH_MAX は M_GRID_SIZE以下でなければならない
static_assert(M_SEARCH_MAX <= M_GRID_SIZE, "M_SEARCH_MAX must be less than or equal to M_GRID_SIZE");

#endif // CONFIG_HPP