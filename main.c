#include <stdio.h>
#include <getopt.h> // for getopt_long
#include <stdlib.h> // for atoi
#include <ctype.h> // for isDigit
#include <string.h> // for strcmp
#include "src/sread.h"

// NOTE: bool type is defined in "src/sread.h"

void helper() {
    puts("SRead is a tool to read/write from/into serial ports under POSIX systems\n"
         "-h, --help  | Print this helper\n"
         "-r, --read  | Read from specified device/port\n"
         "-w, --write | Write to specified device/port\n"
         "-d, --data  | Data to write to device/port\n"
         "-b, --baud  | Specify baud rate\n"
         "-a, --about | About this tool");
}

int main(int argc, char **argv) {
    if(argc < 2) { // Return on wrong number of arguments
        puts("Error: pass argv[1] something(--help for the helper)");
        return -1;
    }

    int opt; // User choice
    const char *short_opts = "r:w:d:b:ha"; // List of parameters. The colon means additional argument
    struct option long_opts[] = {
        {"read", required_argument, NULL, 'r'},
        {"write", required_argument, NULL, 'w'},
        {"data", required_argument, NULL, 'd'},
        {"baud", required_argument, NULL, 'b'},
        {"help", no_argument, NULL, 'h'},
        {"about", no_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}
    };

    // Standard values
    unsigned int baud_rate = 9600;
    bool read_opt = false, write_opt = false;
    char *data = NULL, *device_name = NULL;

    while((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        switch (opt) {
        case 'r':
            if(write_opt) {
                puts("Error: only one operation at the time is supported");
                return 1;
            }
            // Otherwise enable operation flag
            read_opt = true;
            // And retrieve device to read from
            device_name = optarg;
            break;

        case 'w':
            if(read_opt) {
                puts("Error: only one operation at the time is supported");
                return 1;
            }
            // Otherwise enable operation flag
            write_opt = true;
            // And retrieve device to write into
            device_name = optarg;
            break;
        
        case 'd':
            data = optarg;
            break;
        
        case 'b':
            baud_rate = atoi(optarg);
            break;

        case 'a':
            puts("SRead is a tool to read/write from/into serial devices under POSIX systems\n Develop by Marco 'icebit' Cetica (c) 2019-2020");
            return 0;
        
        case 'h':
            helper();
            return 0;

        case ':':
        case '?':
        default:
            return 1;
        }
    }

    // Check which operation user has choosen
    if(read_opt == true) {
        // Create output buffer
        char buf[64];

        // Open port and retrieve data
        open_port(device_name, baud_rate);
        read_from_port(buf, 64);

        // keep reading until buffer is empty
         do {
            printf("%s", buf);
            read_from_port(buf, 64);
        } while(buf[0] != '\0');

        // Close port
        close_port();
        return 0;
    } else if(write_opt == true) {
        // First check if data buffer is set
        if(data == NULL) {
            puts("Error: specify data to write into device(--help for the helper)");
            return 1;
        }

        // Open port
        open_port(device_name, baud_rate);
        // Write data to device
        write_to_port(data, strlen(data));
        // Last, close port
        close_port(device_name);
    } else {
        puts("Error: use this option only with --read or --write.");
        return 1;
    }

    return 0;
}
