#pragma once
#include <cstdint>

class Crc {
public:
    uint32_t crc32(const uint8_t *b, uint32_t l);
};
