#include "sread.h"

void open_port(const char *port_name, bool echo_mode, unsigned short baud_rate) {
    // Try to open the port and saving the file descriptor
    serial_port = open(port_name, O_RDWR);

    // Handle errors
    if(serial_port < 0) {
        fprintf(stderr, "Unable to open device '%s', if the device actually exists, check user permissions.\n", port_name);
        return;
    }

    // Configure tty
    configure_termios(echo_mode);

    // Update port status
    port_status = OPENED;
    printf("Device '%s' opened successfully!\n", port_name);
}

void configure_termios(bool echo_mode, unsigned short baud_rate) {
    // Create a termios struct
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Handle errors
    if(tcgetattr(serial_port, &tty) != 0) {
        fprintf(stderr, "Error %d from tcgetattr: %s\n", errno, strerror(errno));
        return;
    }

    // Configure c_cflags
    tty.c_cflag &= ~PARENB; // Disable parity bit, most serial communication doesn't use it anyway
    tty.c_cflag &= ~CSTOPB; // USe only one stop bit 
    tty.c_cflag |= CS8; // Define 1 byte as 8 bits
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control(if available)
    tty.c_cflag |= CREAD | CLOCAL; // Enable read operations and ignore SIGHUP

    // Configure c_lflags
    tty.c_lflag &= ~ICANON; // Disable canonical mode(i.e. input is not line-oriented anymore)
    echo_mode ? (tty.c_lflag | ECHO) : (tty.c_cflag & ~(ECHO)); // Enable or disable echo mode
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new line on echo
    tty.c_lflag &= ~ISIG; // Disable INTR, QUIT, SUSP interpretation

    // Configure c_iflag (low level settings for input processing)
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable special handling

    // Configure c_oflag (low leve settings for output processing)
    tty.c_oflag &= ~OPOST; // Disable special interpretation
    tty.c_oflag &= ~ONLCR; // Prevent conversion to new line to carriage return 

    // Configure c_cc
    /* When VMIN is 0, VTIME specifies a timeout from the start of the read() syscall,
        however, when VMIN is > 0, VTIME specifies a timeout from the start of the first
        received character
        - VMIN = 0, VTIME = 0 -> No blocking, return immediately with what is available
        - VMIN > 0, VTIME = 0 -> This will make read() always wait for bytes
        - VMIN = 0, VTIME > 0 -> Blocked until some data is available or until timeout
        - VMIN > 0, VTIME > 0 -> Block until either VMIN characters have been received or 
          VTIME after first character has elapsed 
        In this case i want to read at least 10 symbols at the time */

    tty.c_cc[VTIME] = 0; // Wait indefinitely
    tty.c_cc[VMIN] = 10; // Read at least 10 symbols
    
    // Configure baud rate
    switch (baud_rate)
    {
    case 9600:
        cfsetispeed(&tty, B9600); // Set the input baud 
        cfsetospeed(&tty, B9600); // Set the output baud rate
        break;
    
    case 38400:
        cfsetispeed(&tty, B38400); // Set the input baud 
        cfsetospeed(&tty, B38400); // Set the output baud rate
        break;

    case 57600:
        cfsetispeed(&tty, B57600); // Set the input baud 
        cfsetospeed(&tty, B57600); // Set the output baud rate
        break;

    case 115200:
        cfsetispeed(&tty, B115200); // Set the input baud 
        cfsetospeed(&tty, B115200); // Set the output baud rate
        break;
    
    default:
        fprintf(stderr, "Baud rate not supported\n");
        return;
    }

    // Save tty settings
    if(tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        fprintf(stderr, "Error %d from tcsetattr: %s\n", errno, strerror(errno));
        return;
    }
}