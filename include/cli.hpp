#pragma once
#include <cstdint>

struct Cfg {
    char dev[64] = "/dev/ttyUSB0";
    uint32_t baud = 1000000;
    char cmd[16] = "id";
    uint32_t addr = 0x08000000;
    uint32_t len  = 0x1000;
};

class Cli {
public:
    bool par(int c, char **v, Cfg &o);
};
