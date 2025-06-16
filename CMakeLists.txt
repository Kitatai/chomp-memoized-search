cmake_minimum_required(VERSION 3.15)
project(chomp-enum CXX)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-O3 -march=native)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(ferrers_key src/ferrers_key.cpp)
add_library(memo_table src/memo_table.cpp)
add_library(row_state src/row_state.cpp)
add_library(search src/search.cpp)
add_library(solve src/solve.cpp)

add_executable(chomp_enum src/main.cpp)

target_link_libraries(chomp_enum
ferrers_key memo_table solve search row_state
)
