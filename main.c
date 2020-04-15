#include <stdio.h>
#include <getopt.h>

#define VERSION "0.2"
#define AUTHOR "Marco 'icebit' Cetica"

void helper() {
    puts("SRead is a tool to read/write from/into serial ports under POSIX systems\n"
         "-h, --help  | Print this helper\n"
         "-r, --read  | Read from specified device/port\n"
         "-w, --write | Write to specified device/port\n"
         "-d, --data  | Data to write to device/port\n"
         "-b, --baud  | Specify baud rate\n"
         "-e, --echo  | Enable or disable echo mode\n"
         "-a, --about | About this tool");
}

int main(int argc, char **argv) {
    if(argc < 2) { // Return on wrong number of arguments
        puts("Error: pass argv[1] something(--help for the helper)");
        return -1;
    }

    int opt; // User choice
    const char *short_opts = "r:w:d:b:e:ha"; // List of parameters. The colon means additional argument
    struct option long_opts[] = {
        {"read", required_argument, NULL, 'r'},
        {"write", required_argument, NULL, 'w'},
        {"data", required_argument, NULL, 'd'},
        {"baud", required_argument, NULL, 'b'},
        {"echo", required_argument, NULL, 'e'},
        {"help", no_argument, NULL, 'h'},
        {"about", no_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}
    };

    while((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        /* TODO:
         * 1. Set baud rate to 9600 and echo mode to false (default values)
         * 2. check if opposite opt flag is false
         * 3. Set opt to choosen one
         * 4. retrieve port/device
         * 5. At the end of the switch if data buffer is empty print an error msg
         * 6. If not call the appropriate function according to opt var. */
    }


    return 0;
}