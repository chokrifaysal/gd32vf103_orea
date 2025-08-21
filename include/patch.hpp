#pragma once
#include <cstdint>
#include "uart.hpp"

class Patch {
public:
    bool wr(Uart *u, uint32_t a, const uint8_t *d, uint32_t l);
};
