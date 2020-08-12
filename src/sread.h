#ifndef SREAD_H
#define SREAD_H

/* Linux C APIs */
#include <stdio.h>
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h> // Standard constants and types
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number costants
#include <string.h> // For memset
#include <stdlib.h> // For exit

// Status enum
typedef enum {
    CLOSED,
    OPENED
}Status;

// Public APIs
void open_port(const char *port_name, unsigned int baud_rate);
void close_port();
void write_to_port(const char data[], size_t data_size);
void read_from_port(char *buf, size_t buf_size);

#endif
