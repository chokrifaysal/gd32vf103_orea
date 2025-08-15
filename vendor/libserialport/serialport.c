#include <libserialport.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

struct sp_port {
    char name[64];
    int fd;
};

enum sp_return sp_get_port_by_name(const char *name, struct sp_port **port_ptr) {
    struct sp_port *p = (struct sp_port *)malloc(sizeof(struct sp_port));
    if (!p) return SP_ERR_MEM;
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    *port_ptr = p;
    return SP_OK;
}

enum sp_return sp_open(struct sp_port *port, enum sp_mode mode) {
    (void)mode;
    int fd = open(port->name, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) return SP_ERR_FAIL;
    port->fd = fd;
    return SP_OK;
}

enum sp_return sp_close(struct sp_port *port) {
    if (close(port->fd) < 0) return SP_ERR_FAIL;
    return SP_OK;
}

void sp_free_port(struct sp_port *port) {
    free(port);
}

enum sp_return sp_set_baudrate(struct sp_port *port, int baudrate) {
    struct termios t;
    if (tcgetattr(port->fd, &t) < 0) return SP_ERR_FAIL;
    speed_t br;
    switch (baudrate) {
        case 9600:   br = B9600;   break;
        case 115200: br = B115200; break;
        default: return SP_ERR_ARG;
    }
    cfsetispeed(&t, br);
    cfsetospeed(&t, br);
    if (tcsetattr(port->fd, TCSANOW, &t) < 0) return SP_ERR_FAIL;
    return SP_OK;
}

enum sp_return sp_set_bits(struct sp_port *port, int bits) {
    struct termios t;
    if (tcgetattr(port->fd, &t) < 0) return SP_ERR_FAIL;
    t.c_cflag &= ~CSIZE;
    switch (bits) {
        case 8: t.c_cflag |= CS8; break;
        default: return SP_ERR_ARG;
    }
    if (tcsetattr(port->fd, TCSANOW, &t) < 0) return SP_ERR_FAIL;
    return SP_OK;
}

enum sp_return sp_set_parity(struct sp_port *port, enum sp_parity parity) {
    struct termios t;
    if (tcgetattr(port->fd, &t) < 0) return SP_ERR_FAIL;
    if (parity == SP_PARITY_NONE) {
        t.c_cflag &= ~PARENB;
    } else {
        return SP_ERR_ARG;
    }
    if (tcsetattr(port->fd, TCSANOW, &t) < 0) return SP_ERR_FAIL;
    return SP_OK;
}

enum sp_return sp_set_stopbits(struct sp_port *port, int stopbits) {
    struct termios t;
    if (tcgetattr(port->fd, &t) < 0) return SP_ERR_FAIL;
    if (stopbits == 1) {
        t.c_cflag &= ~CSTOPB;
    } else {
        return SP_ERR_ARG;
    }
    if (tcsetattr(port->fd, TCSANOW, &t) < 0) return SP_ERR_FAIL;
    return SP_OK;
}

int sp_blocking_read(struct sp_port *port, void *buf, size_t len, unsigned timeout_ms) {
    (void)timeout_ms;
    return read(port->fd, buf, len);
}

int sp_blocking_write(struct sp_port *port, const void *buf, size_t len, unsigned timeout_ms) {
    (void)timeout_ms;
    return write(port->fd, buf, len);
}
