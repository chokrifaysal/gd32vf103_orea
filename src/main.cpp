#include <cstdio>
#include <cstring>
#include "cli.hpp"
#include "uart.hpp"
#include "probe.hpp"
#include "core.hpp"
#include "flash.hpp"
#include "file.hpp"
#include "crc.hpp"

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

    if (cfg.v) std::printf("idcode: 0x%08lX\n", p.id());

    Core co;
    if (!co.hlt(&u)) {
        std::fprintf(stderr, "halt fail\n");
        return 1;
    }

    if (std::strcmp(cfg.cmd, "id") == 0) {
        if (!cfg.v) std::printf("0x%08lX\n", p.id());
    } else if (std::strcmp(cfg.cmd, "dump") == 0) {
        uint8_t *buf = new uint8_t[cfg.len];
        Flash f;
        if (!f.rd(&u, cfg.addr, buf, cfg.len)) {
            std::fprintf(stderr, "dump fail\n");
            delete[] buf;
            return 1;
        }
        Crc crc;
        uint32_t c = crc.crc32(buf, cfg.len);
        File fl;
        if (!fl.wr(cfg.file, buf, cfg.len)) {
            std::fprintf(stderr, "file fail\n");
            delete[] buf;
            return 1;
        }
        if (cfg.v) std::printf("dump ok -> %s  crc32=0x%08lX\n", cfg.file, c);
        delete[] buf;
    } else if (std::strcmp(cfg.cmd, "erase") == 0) {
        Flash f;
        if (!f.erase(&u, cfg.addr, cfg.addr + cfg.len)) {
            std::fprintf(stderr, "erase fail\n");
            return 1;
        }
        if (cfg.v) std::puts("erase ok");
    } else if (std::strcmp(cfg.cmd, "flash") == 0) {
        uint8_t *buf = new uint8_t[cfg.len];
        File fl;
        if (!fl.rd(cfg.file, buf, cfg.len)) {
            std::fprintf(stderr, "file fail\n");
            delete[] buf;
            return 1;
        }
        Crc crc;
        uint32_t c = crc.crc32(buf, cfg.len);
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
        uint8_t *chk = new uint8_t[cfg.len];
        if (!f.rd(&u, cfg.addr, chk, cfg.len)) {
            std::fprintf(stderr, "verify fail\n");
            delete[] buf;
            delete[] chk;
            return 1;
        }
        uint32_t v = crc.crc32(chk, cfg.len);
        delete[] buf;
        delete[] chk;
        if (c != v) {
            std::fprintf(stderr, "verify crc mismatch 0x%08lX != 0x%08lX\n", c, v);
            return 1;
        }
        if (cfg.v) std::printf("flash ok <- %s  crc32=0x%08lX\n", cfg.file, c);
    } else {
        std::fprintf(stderr, "unknown cmd\n");
        return 1;
    }

    return 0;
}
