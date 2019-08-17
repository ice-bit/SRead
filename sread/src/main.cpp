#include <iostream>
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
         std::string port_name;
         int baud_rate;

         options_description desc("Allowed options");
         desc.add_options()
         /* Parameters are organized in the following way:
          * First parameter: describes option name
          * Second parameter: the actual option
          * Third one: the description
          */
         ("help,h", "Print the helper")
         ("read,r", value(&port_name), "Read from device/port")
         ("write,w", value(&port_name), "Write to device/port")
         ("baud,b", value(&baud_rate), "Specify baud rate");

         variables_map vm;
         store(parse_command_line(argc, argv, desc), vm);

         /* Check if baud rate is specified when
          * read/write operations are required.
          */
         option_dependency(vm, "read", "baud");
         option_dependency(vm, "write", "baud");

         if(vm.count("help")) {
             std::cout << desc << std::endl;
             return 0;
         }
         else if(vm.count("name"))
             std::cout << "Hello " << vm["name"].as<std::string>() << std::endl;
     }
     catch(std::exception &e) {
         std::cerr << e.what() << std::endl;
     }
 }