#include "../include/serial_read.h"

serial_read::serial_read(const std::string device_name, PosixBaudRates baud_rate, const unsigned int timeout, const bool echoMode) {
    this->device_name = device_name;
    this->baud_rate = baud_rate;
    this->timeout = timeout;
    this->echoMode = echoMode;
}
