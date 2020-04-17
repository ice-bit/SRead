#ifndef SREAD_H
#define SREAD_H

/* Linux C APIs */
#include <stdio.h>
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h> // Standard constants and types
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number costants

// Status enum
enum Status {
    CLOSED,
    OPENED
};

// Internal functions
static void open_port(const char *port_name);
static void configure_termios();
int serial_port = NULL; // Result of the open function

// Public APIs
void write_to_port(const char* data);
char *read_from_port();
Status port_status = Status::CLOSED;

#endif