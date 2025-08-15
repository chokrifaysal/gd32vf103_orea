#include "flash.hpp"
#include "core.hpp"
#include <cstdio>

bool Flash::erase(Uart *u, uint32_t s, uint32_t e) {
    (void)u; (void)s; (void)e;
    /* TODO: real algo */
    return true;
}

bool Flash::wr(Uart *u, uint32_t a, const uint8_t *d, uint32_t l) {
    (void)u; (void)a; (void)d; (void)l;
    /* TODO: real algo */
    return true;
}

bool Flash::rd(Uart *u, uint32_t a, uint8_t *d, uint32_t l) {
    (void)u; (void)a; (void)d; (void)l;
    /* TODO: real algo */
    return true;
}

bool Flash::wait(Uart *u) {
    (void)u;
    /* TODO: real algo */
    return true;
}
