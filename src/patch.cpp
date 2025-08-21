#include "patch.hpp"
#include "flash.hpp"
#include "core.hpp"

bool Patch::wr(Uart *u, uint32_t a, const uint8_t *d, uint32_t l) {
    Flash f;
    return f.wr(u, a, d, l);
}
