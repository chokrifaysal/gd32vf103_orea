#pragma once
#include <cstdint>
#include "uart.hpp"

class Flash {
public:
    bool erase(Uart *u, uint32_t s, uint32_t e);
    bool wr(Uart *u, uint32_t a, const uint8_t *d, uint32_t l);
    bool rd(Uart *u, uint32_t a, uint8_t *d, uint32_t l);
private:
    bool wait(Uart *u);
};
