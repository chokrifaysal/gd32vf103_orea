#pragma once
#include <cstdint>

class Uart;

class Swd {
public:
    bool init();
    void rst();
    bool wr(Uart *u, uint8_t cmd, uint32_t data);
    bool rd(Uart *u, uint8_t cmd, uint32_t &data);
private:
    uint8_t crc(uint8_t *b, int n);
    bool txrx(Uart *io, uint8_t *b, int n, int r);
    static const int max_try = 4;
};
