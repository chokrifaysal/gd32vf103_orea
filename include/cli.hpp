#pragma once
#include <cstdint>

struct Cfg {
    char dev[64] = "/dev/ttyUSB0";
    uint32_t baud = 1000000;
};

class Cli {
public:
    bool par(int c, char **v, Cfg &o);
};
