#include "file.hpp"
#include <cstdio>

bool File::wr(const char *p, const uint8_t *d, uint32_t l) {
    FILE *f = std::fopen(p, "wb");
    if (!f) return false;
    std::fwrite(d, 1, l, f);
    std::fclose(f);
    return true;
}

bool File::rd(const char *p, uint8_t *d, uint32_t l) {
    FILE *f = std::fopen(p, "rb");
    if (!f) return false;
    std::fread(d, 1, l, f);
    std::fclose(f);
    return true;
}
