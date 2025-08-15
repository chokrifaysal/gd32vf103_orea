#include "swd.hpp"
#include "uart.hpp"
#include <cstdio>

static uint8_t crc7(uint8_t *b, int n) {
    uint8_t crc = 0x7F;
    for (int i = 0; i < n; ++i) {
        crc ^= b[i];
        for (int k = 0; k < 8; ++k)
            crc = (crc & 1) ? (crc >> 1) ^ 0x91 : (crc >> 1);
    }
    return crc;
}

bool Swd::init() { return true; }

void Swd::rst() {
    uint8_t seq[8] = {0xFF};
    for (int i = 0; i < 8; ++i) txrx(seq, 1);
}

bool Swd::wr(uint8_t cmd, uint32_t data) {
    uint8_t hdr[4] = {cmd, (uint8_t)data, (uint8_t)(data >> 8), (uint8_t)(data >> 16)};
    hdr[0] |= (crc7(hdr, 4) << 5);
    if (!txrx(hdr, 4)) return false;
    uint8_t ack[3] = {0};
    if (!txrx(ack, 3)) return false;
    return ack[0] == 0x01;
}

bool Swd::rd(uint8_t cmd, uint32_t &data) {
    uint8_t hdr[1] = {cmd};
    hdr[0] |= (crc7(hdr, 1) << 5
