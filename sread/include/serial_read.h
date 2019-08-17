#ifndef SERIAL_READ_H
#define SERIAL_READ_H

#include <string>

/* Linux C headers */
#include <termios.h>
#include <unistd.h>

class serial_read {
public:
    


private:
    int read_port(std::string port_name);
    unsigned int port_number_descriptor;  // Result of open function
    std::string device_name; // Device name
    /* static constexpr */ unsigned int baud_rate;
    static constexpr int timeout = -1; 
};


#endif