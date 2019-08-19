#include "../include/serial_read.h"

serialRead::serialRead(const std::string device_name, PosixBaudRates baud_rate, const int timeout, const bool echoMode) {
    this->device_name = device_name;
    this->baud_rate = baud_rate;
    this->timeout = timeout;
    this->echoMode = echoMode;
}

void serialRead::open_port(std::string port_name) {
    // Try to open port and saving descriptor
    this->serial_port = open(port_name.c_str(), O_RDWR);

    // Check for errors
    if(this->serial_port < 0)
        throw std::logic_error(std::string("Unable to open device '" + port_name + "', if the device actually exists, check user permissions."));


    // TODO: call configure_termios()

    std::cout << "Device '" << port_name << "' opened successfully!" << std::endl;
    this->port_status = Status::OPENED;
}

void serialRead::configure_termios() {
     // Create a termios struct
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Check for errors
    if(tcgetattr(this->serial_port, &tty) != 0)
        std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;

    /* Configure c_cflag */
    tty.c_cflag &= ~PARENB; // Disable parity bit, since most serial communications don't use it
    tty.c_cflag &= ~CSTOPB; // Use only one stop bit
    tty.c_cflag |= CS8; // We use 8 bits per byte(it's the most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable read operations and ignore SIGHUP signal

    /* Configure c_lflag */
    tty.c_lflag &= ~ICANON; // Disable canonical mode(e.g. do not process data on new lines)
    this->echoMode ? (tty.c_lflag | ECHO) : (tty.c_lflag & ~(ECHO)); // Enable or disable echo mode
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new line echo
    tty.c_lflag &= ~ISIG; // Disable INTR, QUIT, SUSP interpretation

    /* Configure c_iflag (low level settings for input processing) */
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable special handling
    
    /* Configure c_oflag (low level settings for output processing) */
    tty.c_oflag &= ~OPOST; // Disable special interpretation
    tty.c_oflag &= ~ONLCR; // Prevent conversion to new line to carriage return

    /* Configure c_cc */
    /* When VMIN is 0, VTIME specifies a timeout from the start of the read() syscall,
    however, when VMIN is > 0, VTIME specifies a timeout from the start of the first
    received character 
    - VMIN = 0, VTIME = 0 -> No blocking, return immediately with what is available
    - VMIN > 0, VTIME = 0 -> This will make read() always wait for bytes
    - VMIN = 0, VTIME > 0 -> Blocked until some data is available or until timeout
    - VMIN > 0, VTIME > 0 -> Block until either VMIN characters have been received or 
        VTIME after first character has elapsed */

    if(this->timeout == -1) {
        // Wait for one byte
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 1;
    } else if(this->timeout == 0) {
        // Set a non-blocking read
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 0;
    } else if(this->timeout > 0) {
        tty.c_cc[VTIME] = (cc_t)(this->timeout / 100);
        tty.c_cc[VMIN] = 0;
    }

    
    
}