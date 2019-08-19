#include <iostream>
#include "../include/serial_read.h"
#include <boost/program_options.hpp>

using namespace boost::program_options;

/* Check if parameter requires another parameter */
void option_dependency(const variables_map &vm, const char *for_what, const char *required_option) {
    if(vm.count(for_what) && !vm[for_what].defaulted())
        if(vm.count(required_option) == 0 || vm[required_option].defaulted())
            throw std::logic_error(std::string("Option '") + for_what  + "' requires option '" + required_option + "'.");
 }

 int main(int argc, char *argv[]) {
     // Check if arguments were provided at all
     if(argc < 2) {
         std::cerr << "ERROR: use: " << argv[0] << " --help to get a list of options!" << std::endl;
         return -1;
     }
     try {
         options_description desc("Allowed options");
         desc.add_options()
         /* Parameters are organized in the following way:
          * First parameter: describes option name
          * Second parameter: the actual option
          * Third one: the description
          */
         ("help,h", "Print the helper")
         ("read,r", value<std::string>(), "Read from device/port")
         ("write,w", value<std::string>(), "Write to device/port")
         ("baud,b", value<int>(), "Specify baud rate")
         ("echo,e", value<bool>(), "Enable/Disable echo mode")
         ("about,a", "About this tool");

         variables_map vm;
         store(parse_command_line(argc, argv, desc), vm);
         //std::string write_port_name = vm["write"].as<std::string>();


         /* Check if baud rate and echo are specified when
          * read/write operations are called.
          */
         option_dependency(vm, "read", "baud");
         option_dependency(vm, "read", "echo");
         option_dependency(vm, "write", "baud");
         option_dependency(vm, "write", "echo");

         if(vm.count("help")) {
             std::cout << "SRead is a tool to read/write from/into serial ports under POSIX systems\n" << std::endl;
             std::cout << desc << std::endl;
             return 0;
         } else if(vm.count("read")) {
             // Retrieve arguments
            std::string read_port_name = vm["read"].as<std::string>();
            int baud_rate = vm["baud"].as<int>();
            bool echo_mode = vm["echo"].as<bool>();
            // Create output vector
            std::string outputBuffer;
            // Create a new object 
            serialRead sr(read_port_name, baud_rate, echo_mode);
            // Read from port
            outputBuffer = sr.read_from_port();
            // Print until we get some data
            while(outputBuffer != "") {
                std::cout << outputBuffer;
                outputBuffer = sr.read_from_port();
            }
            // Close port
            std::cout << "\nClosing port..." << std::endl;
            sr.close_port();
            std::cout << "Serial communication interrupted" << std::endl;
         } else if(vm.count("baud") || vm.count("echo"))
             std::cerr << "This option must be used with --read/--write arguments." << std::endl;
     }
     catch(std::exception &e) {
         std::cerr << e.what() << std::endl;
     }
 }