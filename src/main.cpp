#include <cstdio>
#include "cli.hpp"
#include "uart.hpp"
#include "swd.hpp"
#include "probe.hpp"
#include "core.hpp"

int main(int c, char **v) {
    Cfg cfg;
    Cli cli;
    if (!cli.par(c, v, cfg)) return 1;

    Uart u;
    if (!u.op(cfg.dev, cfg.baud)) {
        std::fprintf(stderr, "uart fail\n");
        return 1;
    }

    Probe p;
    if (!p.dap(&u)) {
        std::fprintf(stderr, "probe fail\n");
        return 1;
    }

    uint32_t id = p.id();
    std::printf("idcode: 0x%08lX\n", id);

    Core c;
    if (!c.hlt(&u)) {
        std::fprintf(stderr, "halt fail\n");
        return 1;
    }

    std::puts("core halted");
    return 0;
}
