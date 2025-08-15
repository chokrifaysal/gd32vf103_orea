#include "uart.hpp"
#include <libserialport.h>

Uart::Uart() {}

Uart::~Uart() { cl(); }

bool Uart::op(const char *p, uint32_t b) {
    sp_port *pt;
    if (sp_get_port_by_name(p, &pt) != SP_OK) return false;
    if (sp_open(pt, SP_MODE_READ_WRITE) != SP_OK) return false;
    sp_set_baudrate(pt, b);
    sp_set_bits(pt, 8);
    sp_set_parity(pt, SP_PARITY_NONE);
    sp_set_stopbits(pt, 1);
    h = pt;
    return true;
}

void Uart::cl() {
    if (!h) return;
    sp_close(static_cast<sp_port*>(h));
    sp_free_port(static_cast<sp_port*>(h));
    h = nullptr;
}

int Uart::rd(uint8_t *b, int l) {
    if (!h) return -1;
    return sp_blocking_read(static_cast<sp_port*>(h), b, l, 0);
}

int Uart::wr(const uint8_t *b, int l) {
    if (!h) return -1;
    return sp_blocking_write(static_cast<sp_port*>(h), b, l, 0);
}
