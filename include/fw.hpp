#pragma once
#include <cstdint>
#include "uart.hpp"

class Fw {
public:
    bool dump(Uart *u, uint32_t a, uint32_t l);
};
