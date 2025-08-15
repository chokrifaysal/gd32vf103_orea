#pragma once
#include <cstdint>
#include "uart.hpp"

class Core {
public:
    bool hlt(Uart *u);
    bool run(Uart *u);
    bool wr32(Uart *u, uint32_t a, uint32_t v);
    bool rd32(Uart *u, uint32_t a, uint32_t &v);
};
