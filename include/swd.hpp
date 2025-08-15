#pragma once
#include <cstdint>

class Uart;

class Swd {
public:
    bool init();
    void rst();
    bool wr(uint8_t cmd, uint32_t data);
    bool rd(uint8_t cmd, uint32_t &data);
    void set_io(Uart *u);
private:
    uint8_t crc(uint8_t *b, int n);
    bool txrx(uint8_t *b, int n, int r);
    Uart *io = nullptr;
};
