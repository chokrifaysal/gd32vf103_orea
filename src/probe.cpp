#include "probe.hpp"
#include "uart.hpp"
#include <cstdio>

static const uint8_t dap_info[] = {0x00, 0x04};
static const uint8_t dap_conn[] = {0x02, 0x01, 0x00};
static const uint8_t dap_swj_clk[] = {0x11, 0x01, 0x00, 0x00, 0x00};
static const uint8_t dap_swj_seq[] = {0x12, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t dap_trans_req[] = {0x05, 0x01, 0x00, 0x05, 0xA5, 0x00, 0x00, 0x00, 0x00};

bool Probe::dap(Uart *u) {
    io = u;
    uint8_t buf[64];

    if (!tx(dap_info, sizeof(dap_info))) return false;
    if (!rx(buf, 3)) return false;

    if (!tx(dap_conn, sizeof(dap_conn))) return false;
    if (!rx(buf, 2)) return false;

    if (!tx(dap_swj_clk, sizeof(dap_swj_clk))) return false;
    if (!rx(buf, 2)) return false;

    if (!tx(dap_swj_seq, sizeof(dap_swj_seq))) return false;
    if (!rx(buf, 2)) return false;

    return true;
}

uint32_t Probe::id() {
    uint8_t buf[64];
    if (!tx(dap_trans_req, sizeof(dap_trans_req))) return 0;
    if (!rx(buf, 7)) return 0;
    uint32_t idc = buf[3] | (buf[4] << 8) | (buf[5] << 16) | (buf[6] << 24);
    return idc;
}

bool Probe::tx(const uint8_t *b, int l) {
    if (!io) return false;
    uint8_t hdr[1] = {0x00};
    return io->wr(hdr, 1) == 1 && io->wr(b, l) == l;
}

bool Probe::rx(uint8_t *b, int l) {
    if (!io) return false;
    uint8_t hdr[1] = {0x00};
    return io->rd(hdr, 1) == 1 && io->rd(b, l) == l;
}
