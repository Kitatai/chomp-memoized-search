#ifndef SOLVE_HPP
#define SOLVE_HPP

#include <vector>
#include <utility>

std::vector<std::pair<int, int>> solve_internal(int n_small, int m_small);
std::vector<std::pair<int, int>> solve_wrapper(int n, int m);

#endif // SOLVE_HPP