#include <cstdio>
#include <cstring>
#include "cli.hpp"
#include "uart.hpp"
#include "probe.hpp"
#include "core.hpp"
#include "fw.hpp"
#include "flash.hpp"

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
        if (!c.hlt(&u)) { std::fprintf(stderr, "halt fail\n"); return 1; }
        uint8_t buf[256];
        Flash f;
        if (!f.rd(&u, cfg.addr, buf, sizeof(buf))) {
            std::fprintf(stderr, "dump fail\n");
            return 1;
        }
        for (uint32_t i = 0; i < sizeof(buf); ++i) {
            std::printf("%02X%c", buf[i], ((i + 1) & 0xF) ? ' ' : '\n');
        }
    } else if (std::strcmp(cfg.cmd, "erase") == 0) {
        Core c;
        if (!c.hlt(&u)) { std::fprintf(stderr, "halt fail\n"); return 1; }
        Flash f;
        if (!f.erase(&u, cfg.addr, cfg.addr + cfg.len)) {
            std::fprintf(stderr, "erase fail\n");
            return 1;
        }
        std::puts("erase ok");
    } else {
        std::fprintf(stderr, "unknown cmd\n");
        return 1;
    }

    return 0;
}
