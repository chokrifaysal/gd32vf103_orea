#include <cstdio>
#include "uart.hpp"
#include "swd.hpp"

int main() {
    std::puts("orea");
    Uart u;
    Swd s;
    s.set_io(&u);
    return 0;
}
