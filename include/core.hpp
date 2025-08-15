#pragma once
#include <cstdint>
#include "uart.hpp"

class Core {
public:
    bool hlt(Uart *u);
    bool run(Uart *u);
private:
    bool wr32(uint32_t a, uint32_t v);
    bool rd32(uint32_t a, uint32_t &v);
};
