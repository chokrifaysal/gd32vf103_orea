#pragma once
#include <cstdint>

class Uart {
public:
    Uart();
    ~Uart();
    bool op(const char *p, uint32_t b);
    void cl();
    int rd(uint8_t *b, int l);
    int wr(const uint8_t *b, int l);
private:
    void *h = nullptr;
};
