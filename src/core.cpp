#include "core.hpp"
#include "probe.hpp"
#include <cstdio>

static bool dap_wr32(Uart *io, uint32_t a, uint32_t v) {
    uint8_t buf[12] = {0x05, 0x01, 0x00, 0x0B, 0xA5,
                       (uint8_t)a, (uint8_t)(a >> 8),
                       (uint8_t)(a >> 16), (uint8_t)(a >> 24),
                       (uint8_t)v, (uint8_t)(v >> 8),
                       (uint8_t)(v >> 16), (uint8_t)(v >> 24)};
    return io->wr(buf, 12) == 12;
}

static bool dap_rd32(Uart *io, uint32_t a, uint32_t &v) {
    uint8_t buf[12] = {0x05, 0x01, 0x00, 0x0B, 0xA1,
                       (uint8_t)a, (uint8_t)(a >> 8),
                       (uint8_t)(a >> 16), (uint8_t)(a >> 24)};
    if (io->wr(buf, 9) != 9) return false;
    uint8_t rx[8];
    if (io->rd(rx, 8) != 8) return false;
    v = rx[4] | (rx[5] << 8) | (rx[6] << 16) | (rx[7] << 24);
    return true;
}

bool Core::hlt(Uart *u) {
    return wr32(u, 0xE000EDF0, 0xA05F0003);
}

bool Core::run(Uart *u) {
    return wr32(u, 0xE000EDF0, 0xA05F0000);
}

bool Core::wr32(uint32_t a, uint32_t v) { return dap_wr32(io, a, v); }
bool Core::rd32(uint32_t a, uint32_t &v) { return dap_rd32(io, a, v); }
