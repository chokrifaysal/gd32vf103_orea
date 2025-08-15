#pragma once
#include <cstdint>

class File {
public:
    bool wr(const char *p, const uint8_t *d, uint32_t l);
    bool rd(const char *p, uint8_t *d, uint32_t l);
};
