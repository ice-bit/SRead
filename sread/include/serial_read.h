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

// Port Status
enum class Status {
    CLOSED,
    OPENED
};

class serialRead {
public:
    serialRead(const std::string device_name, int baud_rate, const bool echoMode);
    void write_to_port(const std::string &data);
    std::string read_from_port();
    std::vector<char> get_read_output();
    void close_port();

private:
    void open_port(std::string port_name);
    void configure_termios();

    int serial_port;  // Result of open function
    std::string device_name; // Device name
    unsigned int baud_rate;
    static constexpr auto timeout = -1;
    bool echoMode = false; // Enable/Disable echoing of input character
    Status port_status = Status::CLOSED;
    std::vector<char> readVec;
    static constexpr auto defaultReadVecSize = 255;
};

#endif