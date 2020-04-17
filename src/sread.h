#ifndef SREAD_H
#define SREAD_H

/* Linux C APIs */
#include <stdio.h>
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h> // Standard constants and types
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number costants

typedef enum {false, true} bool; // Define bool type

// Status enum
typedef enum {
    CLOSED,
    OPENED
}Status;

// Internal functions
static void open_port(const char *port_name, bool echo_mode, unsigned short baud_rate);
static void configure_termios(bool echo_mode, unsigned short baud_rate);
int serial_port = NULL; // Result of the open function

// Public APIs
void write_to_port(const char* data, bool echo_mode, unsigned short baud_rate);
char *read_from_port(bool echo_mode, unsigned short baud_rate);
Status port_status = CLOSED;

#endif