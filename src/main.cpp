#include <cstdio>
#include <cstring>
#include "cli.hpp"
#include "uart.hpp"
#include "probe.hpp"
#include "core.hpp"
#include "fw.hpp"

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

    if (std::strcmp(cfg.cmd, "id") == 0) {
        uint32_t id = p.id();
        std::printf("idcode: 0x%08lX\n", id);
    } else if (std::strcmp(cfg.cmd, "dump") == 0) {
        Core c;
        if (!c.hlt(&u)) {
            std::fprintf(stderr, "halt fail\n");
            return 1;
        }
        Fw f;
        if (!f.dump(&u, cfg.addr, cfg.len)) {
            std::fprintf(stderr, "dump fail\n");
            return 1;
        }
    }

    return 0;
}
