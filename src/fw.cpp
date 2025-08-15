#include "fw.hpp"
#include <cstdio>

static bool dap_read(Uart *io, uint32_t a, uint32_t &v) {
    uint8_t buf[12] = {0x05, 0x01, 0x00, 0x0B, 0xA1,
                       (uint8_t)a, (uint8_t)(a >> 8),
                       (uint8_t)(a >> 16), (uint8_t)(a >> 24)};
    if (io->wr(buf, 9) != 9) return false;
    uint8_t rx[8];
    if (io->rd(rx, 8) != 8) return false;
    v = rx[4] | (rx[5] << 8) | (rx[6] << 16) | (rx[7] << 24);
    return true;
}

bool Fw::dump(Uart *u, uint32_t a, uint32_t l) {
    for (uint32_t off = 0; off < l; off += 4) {
        uint32_t v;
        if (!dap_read(u, a + off, v)) return false;
        std::printf("%08lX\n", v);
    }
    return true;
}
