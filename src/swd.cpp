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
    return crc & 0x7F;
}

bool Swd::init() { return true; }

void Swd::rst() {
    uint8_t seq[8] = {0xFF};
    for (int i = 0; i < 8; ++i) txrx(seq, 1, 0);
}

bool Swd::wr(uint8_t cmd, uint32_t data) {
    uint8_t hdr[4] = {cmd, (uint8_t)data, (uint8_t)(data >> 8), (uint8_t)(data >> 16)};
    hdr[0] |= (crc7(hdr, 4) << 5);
    if (!txrx(hdr, 4, 0)) return false;
    uint8_t ack = 0;
    if (!txrx(&ack, 1, 1)) return false;
    return ack == 0x01;
}

bool Swd::rd(uint8_t cmd, uint32_t &data) {
    uint8_t hdr[1] = {cmd};
    hdr[0] |= (crc7(hdr, 1) << 5);
    if (!txrx(hdr, 1, 0)) return false;
    uint8_t ack = 0;
    if (!txrx(&ack, 1, 1)) return false;
    if (ack != 0x01) return false;
    uint8_t val[4] = {0};
    if (!txrx(val, 4, 1)) return false;
    uint8_t par = 0;
    if (!txrx(&par, 1, 1)) return false;
    data = val[0] | (val[1] << 8) | (val[2] << 16) | (val[3] << 24);
