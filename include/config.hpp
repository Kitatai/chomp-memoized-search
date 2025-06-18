#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstdint>

static constexpr int N_SEARCH_MAX = 20;
static constexpr int M_SEARCH_MAX = 20;
static constexpr int N_GRID_SIZE = 20;
static constexpr int M_GRID_SIZE = 20;

// N_SEARCH_MAX は N_GRID_SIZE以下でなければならない
static_assert(N_SEARCH_MAX <= N_GRID_SIZE, "N_SEARCH_MAX must be less than or equal to N_GRID_SIZE");
// M_SEARCH_MAX は M_GRID_SIZE以下でなければならない
static_assert(M_SEARCH_MAX <= M_GRID_SIZE, "M_SEARCH_MAX must be less than or equal to M_GRID_SIZE");
// N_GRID_SIZE <= M_GRID_SIZE でなければならない
static_assert(N_GRID_SIZE <= M_GRID_SIZE, "N_GRID_SIZE must be less than M_GRID_SIZE");
// N_GRID_SIZE + M_GRID_SIZE は 128以下を推奨する．実際にはもう少し入るが，安定動作を保証しない
static_assert(N_GRID_SIZE + M_GRID_SIZE <= 128, "N_GRID_SIZE + M_GRID_SIZE should be less than or equal to 128");

#endif // CONFIG_HPP