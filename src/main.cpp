#include <cstdio>
#include <cstring>
#include "cli.hpp"
#include "uart.hpp"
#include "probe.hpp"
#include "core.hpp"
#include "flash.hpp"
#include "file.hpp"

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

    Core co;
    if (!co.hlt(&u)) {
        std::fprintf(stderr, "halt fail\n");
        return 1;
    }

    if (std::strcmp(cfg.cmd, "id") == 0) {
        uint32_t id = p.id();
        std::printf("idcode: 0x%08lX\n", id);
    } else if (std::strcmp(cfg.cmd, "dump") == 0) {
        uint8_t *buf = new uint8_t[cfg.len];
        Flash f;
        if (!f.rd(&u, cfg.addr, buf, cfg.len)) {
            std::fprintf(stderr, "dump fail\n");
            delete[] buf;
            return 1;
        }
        File fl;
        if (!fl.wr(cfg.file, buf, cfg.len)) {
            std::fprintf(stderr, "file fail\n");
            delete[] buf;
            return 1;
        }
        std::printf("dump ok -> %s\n", cfg.file);
        delete[] buf;
    } else if (std::strcmp(cfg.cmd, "erase") == 0) {
        Flash f;
        if (!f.erase(&u, cfg.addr, cfg.addr + cfg.len)) {
            std::fprintf(stderr, "erase fail\n");
            return 1;
        }
        std::puts("erase ok");
    } else if (std::strcmp(cfg.cmd, "flash") == 0) {
        uint8_t *buf = new uint8_t[cfg.len];
        File fl;
        if (!fl.rd(cfg.file, buf, cfg.len)) {
            std::fprintf(stderr, "file fail\n");
            delete[] buf;
            return 1;
        }
        Flash f;
        if (!f.erase(&u, cfg.addr, cfg.addr + cfg.len)) {
            std::fprintf(stderr, "erase fail\n");
            delete[] buf;
            return 1;
        }
        if (!f.wr(&u, cfg.addr, buf, cfg.len)) {
            std::fprintf(stderr, "flash fail\n");
            delete[] buf;
            return 1;
        }
        std::printf("flash ok <- %s\n", cfg.file);
        delete[] buf;
    } else {
        std::fprintf(stderr, "unknown cmd\n");
        return 1;
    }

    return 0;
}
