#ifndef SERIAL_READ_H
#define SERIAL_READ_H

#include <iostream>
#include <cstring>
#include <vector>

/* Linux C headers */
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// Standard POSIX baud rates
enum class PosixBaudRates {
    B_9600,
    B_38400,
    B_57600,
    B_115200
};

// Port Status
enum class Status {
    CLOSED,
    OPENED
};

class serialRead {
public:
    serialRead(const std::string device_name, PosixBaudRates baud_rate, const int timeout, const bool echoMode);
    void open_port(std::string port_name);
    std::vector<char> read_from_port();
    void write_to_port(const std::string &data);
    void close_port(unsigned int port_number);

private:
    void configure_termios();

    int serial_port;  // Result of open function
    std::string device_name; // Device name
    PosixBaudRates baud_rate = PosixBaudRates::B_9600;
    int timeout = -1;
    bool echoMode = false; // Enable/Disable echoing of input character
    Status port_status = Status::CLOSED;
    std::vector<char> readVec;
};


#endif