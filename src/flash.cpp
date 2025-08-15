#include "flash.hpp"
#include "core.hpp"
#include <cstring>
#include <cstdio>

bool Flash::erase(Uart *u, uint32_t s, uint32_t e) {
    Core c;
    /* unlock */
    c.wr32(u, 0x40022004, 0x45670123);
    c.wr32(u, 0x40022004, 0xCDEF89AB);
    /* mass erase */
    c.wr32(u, 0x40022010, 0x00000004);
    c.wr32(u, 0x40022010, 0x00000044);
    if (!wait(u)) return false;
    c.wr32(u, 0x40022010, 0x00000080);
    return true;
}

bool Flash::wr(Uart *u, uint32_t a, const uint8_t *d, uint32_t l) {
    Core c;
    for (uint32_t i = 0; i < l; i += 4) {
        uint32_t w = d[i] | (d[i + 1] << 8) | (d[i + 2] << 16) | (d[i + 3] << 24);
        c.wr32(u, a + i, w);
        if (!wait(u)) return false;
    }
    return true;
}

bool Flash::rd(Uart *u, uint32_t a, uint8_t *d, uint32_t l) {
    Core c;
    for (uint32_t i = 0; i < l; i += 4) {
        uint32_t v;
        if (!c.rd32(u, a + i, v)) return false;
        memcpy(d + i, &v, 4);
    }
    return true;
}

bool Flash::wait(Uart *u) {
    Core c;
    uint32_t sr;
    do {
        if (!c.rd32(u, 0x4002200C, sr)) return false;
    } while (sr & 0x01);
    return true;
}
