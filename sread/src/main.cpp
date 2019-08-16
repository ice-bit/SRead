#include <iostream>
#include <boost/program_options.hpp>

using namespace boost::program_options;


// Check that opt1 and opt2 aren't specified at the
// same time

void conflicting_options(const variables_map &vm, const char *opt1, const char *opt2) {
    if(vm.count(opt1) && !vm[opt1].defaulted() && vm.count(opt2) && !vm[opt2].defaulted())
        throw std::logic_error(std::string("Conflicting options '") + opt1 + "' and '" + opt2 + "'.");
}

void option_dependency(const variables_map &vm, const char *for_what, const char *required_option) {
    if(vm.count(for_what) && !vm[for_what].defaulted())
        if(vm.count(required_option) == 0 || vm[required_option].defaulted())
            throw std::logic_error(std::string("Option '") + for_what 
            + "' requires option '" + required_option + "'.");
 }

 int main(int argc, char *argv[]) {
     // Check if arguments were provided at all
     if(argc < 2) {
         std::cerr << "ERROR: use: " << argv[0] << " --help to get a list of options!" << std::endl;
         return -1;
     }

     try {
         std::string name;

         options_description desc("Allowed options");
         desc.add_options()
         /* Parameters are organized in the following way:
          * First parameter: describes option name
          * Second parameter: the actual option
          * Third one: the description
          */
         ("help,h", "Print the helper")
         ("name,n", value(&name), "Specify your name");

         variables_map vm;
         store(parse_command_line(argc, argv, desc), vm);

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