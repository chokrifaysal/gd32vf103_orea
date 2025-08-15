#include "cli.hpp"
#include <cstring>
#include <cstdio>

bool Cli::par(int c, char **v, Cfg &o) {
    for (int i = 1; i < c; ++i) {
        if (std::strcmp(v[i], "-d") == 0 && i + 1 < c) {
            std::strncpy(o.dev, v[i + 1], sizeof(o.dev) - 1);
            ++i;
        } else if (std::strcmp(v[i], "-b") == 0 && i + 1 < c) {
            o.baud = std::strtoul(v[i + 1], nullptr, 10);
            ++i;
        } else if (std::strcmp(v[i], "-c") == 0 && i + 1 < c) {
            std::strncpy(o.cmd, v[i + 1], sizeof(o.cmd) - 1);
            ++i;
        } else if (std::strcmp(v[i], "-a") == 0 && i + 1 < c) {
            o.addr = std::strtoul(v[i + 1], nullptr, 0);
            ++i;
        } else if (std::strcmp(v[i], "-l") == 0 && i + 1 < c) {
            o.len = std::strtoul(v[i + 1], nullptr, 0);
            ++i;
        } else if (std::strcmp(v[i], "-f") == 0 && i + 1 < c) {
            std::strncpy(o.file, v[i + 1], sizeof(o.file) - 1);
            ++i;
        } else if (std::strcmp(v[i], "-v") == 0) {
            o.v = true;
        } else {
            std::printf("use: %s [-d dev] [-b baud] [-c id|dump|erase|flash] [-a addr] [-l len] [-f file] [-v]\n", v[0]);
            return false;
        }
    }
    return true;
}
