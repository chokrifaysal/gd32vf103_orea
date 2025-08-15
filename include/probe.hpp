#pragma once
#include <cstdint>
#include "uart.hpp"

class Probe {
public:
    bool dap(Uart *u);
    uint32_t id();
private:
    bool tx(const uint8_t *b, int l);
    bool rx(uint8_t *b, int l);
    Uart *io = nullptr;
};
