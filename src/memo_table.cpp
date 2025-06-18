#include "memo_table.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

uint8_t *memo = nullptr;

uint8_t get_state(uint128_t key)
{
    uint128_t bit = key * STATE_BITS;
    uint128_t idx = bit >> 3; // ÷8 → バイト位置
    uint8_t off = bit & 7;    // %8 → ビットオフセット
    return (memo[idx] >> off) & 0x3;
}

void set_state(uint128_t key, uint8_t v)
{
    uint128_t bit = key * STATE_BITS;
    uint128_t idx = bit >> 3;
    uint8_t off = bit & 7;
    // 2 ビットだけクリアして新しい値をセット
    memo[idx] &= ~(0x3u << off);
    memo[idx] |= ((v & 0x3u) << off);
}

void load_memo(const std::string &path)
{
    if (!std::filesystem::exists(path))
        return;
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "load error\n";
        return;
    }
    ifs.read(reinterpret_cast<char *>(memo), MEMO_BYTES);
}

void save_memo(const std::string &path)
{
    std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
    if (!ofs)
    {
        std::cerr << "save error\n";
        return;
    }
    ofs.write(reinterpret_cast<const char *>(memo), MEMO_BYTES);
    ofs.flush();
}

std::string memo_filename()
{
    return std::string{"memo_"} + std::to_string(N_GRID_SIZE) + "x" + std::to_string(M_GRID_SIZE) + ".bin";
}