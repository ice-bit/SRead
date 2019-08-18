#ifndef SERIAL_READ_H
#define SERIAL_READ_H

#include <string>
#include <vector>

/* Linux C headers */
#include <termios.h>
#include <unistd.h>

// Standard POSIX baud rates
enum class PosixBaudRates {
    B_9600,
    B_38400,
    B_57600,
    B_115200
};

// Port Status
enum class Status {
    CLOSE,
    OPEN
};

class serial_read {
public:
    serial_read(const std::string device_name, PosixBaudRates baud_rate, const unsigned int timeout, const bool echoMode);
    int open_port(std::string port_name);
    void configure_termios();
    std::vector<char> read_from_port();
    void write_to_port(const std::string &data);
    void close_port(unsigned int port_number);

private:
    unsigned int port_number_descriptor;  // Result of open function
    std::string device_name; // Device name
    PosixBaudRates baud_rate = PosixBaudRates::B_9600;
    int timeout = -1;
    bool echoMode = false; // Enable/Disable echoing of input character
    std::vector<char> readVec;
};


#endif