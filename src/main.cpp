#include <cstdio>
#include "cli.hpp"
#include "uart.hpp"
#include "swd.hpp"

int main(int c, char **v) {
    Cfg cfg;
    Cli cli;
    if (!cli.par(c, v, cfg)) return 1;

    Uart u;
    if (!u.op(cfg.dev, cfg.baud)) {
        std::fprintf(stderr, "uart fail\n");
        return 1;
    }
    Swd s;
    s.set_io(&u);
    std::printf("orea ready %s %u\n", cfg.dev, cfg.baud);
    return 0;
}
