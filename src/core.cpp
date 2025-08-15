#include "core.hpp"
#include <cstdio>

bool Core::wr32(Uart *u, uint32_t a, uint32_t v) {
    uint8_t buf[12] = {0x05, 0x01, 0x00, 0x0B, 0xA1,
                       (uint8_t)a, (uint8_t)(a >> 8),
                       (uint8_t)(a >> 16), (uint8_t)(a >> 24),
                       (uint8_t)v, (uint8_t)(v >> 8),
                       (uint8_t)(v >> 16), (uint8_t)(v >> 24)};
    return u->wr(buf, 12) == 12;
}

bool Core::rd32(Uart *u, uint32_t a, uint32_t &v) {
    uint8_t buf[9] = {0x05, 0x01, 0x00, 0x0B, 0xA1,
                      (uint8_t)a, (uint8_t)(a >> 8),
                      (uint8_t)(a >> 16), (uint8_t)(a >> 24)};
    if (u->wr(buf, 9) != 9) return false;
    uint8_t rx[8];
    if (u->rd(rx, 8) != 8) return false;
    v = rx[4] | (rx[5] << 8) | (rx[6] << 16) | (rx[7] << 24);
    return true;
}
