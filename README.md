# Chomp Winning‐Move Enumeration

This program exhaustively lists all winning first moves for 2D Chomp on every rectangular board up to size 20×20. It uses memoized Negamax with α–β pruning and a Ferrers‐diagram–based perfect hash to drive the search.

## Usage

```bash
# Clone the repository
git clone https://github.com/Kitatai/chomp-memoized-search.git
cd chomp-memoized-search

# Build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run (will print estimated memory usage first; press Enter to continue)
./chomp_enum
```

## Note
Searching all rectangles up to 20×20 requires on the order of 34 GB of main memory and disk space.
You can reduce both memory and storage requirements (at the cost of maximum solvable size) by lowering the `N_GRID_SIZE` and `M_GRID_SIZE` values in [`include/config.hpp`](include/config.hpp).

## Search Results

![chomp_winning_moves_color.png](images/chomp_winning_moves_color.png)

We found that no rectangular board of size up to 20×20 has more than three winning first moves for the first player.
