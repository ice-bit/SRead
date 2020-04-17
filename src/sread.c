#include "sread.h"

void open_port(const char *port_name) {
    // Try to open the port and saving the file descriptor
    serial_port = open(port_name, O_RDWR);

    // Handle errors
    if(serial_port < 0) {
        fprintf(stderr, "Unable to open device '%s', if the device actually exists, check user permissions.\n", port_name);
        return -1;
    }

    // Configure tty
    configure_termios();

    // Update port status
    port_status = OPENED;
    printf("Device '%s' opened successfully!\n", port_name);
}

void configure_termios() {
    // Create a termios struct
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Handle errors
    if(tcgetattr(serial_port, &tty) != 0) {
        fprintf(stderr, "Error %d from tcgetattr: %s\n", errno, strerror(errno));
        return;
    }
}