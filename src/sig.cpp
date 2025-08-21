#include "sig.hpp"

int Sig::find(const uint8_t *b, uint32_t l, const uint8_t *p, uint32_t pl) {
    for (uint32_t i = 0; i + pl <= l; ++i) {
        bool ok = true;
        for (uint32_t j = 0; j < pl; ++j) {
            if (b[i + j] != p[j]) { ok = false; break; }
        }
        if (ok) return i;
    }
    return -1;
}
