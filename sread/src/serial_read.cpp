#include "../include/serial_read.h"

serialRead::serialRead(const std::string device_name, PosixBaudRates baud_rate, const unsigned int timeout, const bool echoMode) {
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
}