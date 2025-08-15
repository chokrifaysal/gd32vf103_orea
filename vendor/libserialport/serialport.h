#pragma once
#include <stddef.h>

enum sp_return {
    SP_OK,
    SP_ERR_FAIL,
    SP_ERR_MEM,
    SP_ERR_ARG
};

enum sp_mode {
    SP_MODE_READ = 1,
    SP_MODE_WRITE = 2,
    SP_MODE_READ_WRITE = 3
};

enum sp_parity {
    SP_PARITY_NONE = 0
};

struct sp_port;

enum sp_return sp_get_port_by_name(const char *name, struct sp_port **port_ptr);
enum sp_return sp_open(struct sp_port *port, enum sp_mode mode);
enum sp_return sp_close(struct sp_port *port);
void sp_free_port(struct sp_port *port);
enum sp_return sp_set_baudrate(struct sp_port *port, int baudrate);
enum sp_return sp_set_bits(struct sp_port *port, int bits);
enum sp_return sp_set_parity(struct sp_port *port, enum sp_parity parity);
enum sp_return sp_set_stopbits(struct sp_port *port, int stopbits);
int sp_blocking_read(struct sp_port *port, void *buf, size_t len, unsigned timeout_ms);
int sp_blocking_write(struct sp_port *port, const void *buf, size_t len, unsigned timeout_ms);
