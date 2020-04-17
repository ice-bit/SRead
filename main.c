#include <stdio.h>
#include <getopt.h> // for getopt_long
#include <stdlib.h> // for atoi
#include <ctype.h> // for isDigit
#include <string.h> // for strcmp

#define VERSION "0.2"
#define AUTHOR "Marco 'icebit' Cetica"

typedef enum {false, true} bool; // Define bool type

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

    // Standard values
    unsigned short baud_rate = 9600;
    bool echo_mode = false;
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
            // Checking if arg is a number
            if(isdigit(optarg) == 0) {
                puts("Error: baud rate must be a number");
                return 1;
            }
            baud_rate = atoi(optarg);
            break;

        case 'e':
            if((strcmp(optarg, "true") == 0) || atoi(optarg) == 1)
                echo_mode = true;
            else if((strcmp(optarg, "false") == 0) || atoi(optarg) == 0)
                echo_mode = false;
            else {
                puts("Error: use --echo with one of the following parameters: [true|false]");
                return 1;
            }
            break;

        case 'a':
            puts("SRead is a tool to read/write from/into serial devices under POSIX systems\n Develop by Marco 'icebit' Cetica (c) 2019-2020");
            break;
        
        case 'h':
            helper();
            return 0;

        case ':':
        case '?':
        default:
            break;
        }
    }

    // Check which operation user has choosen
    if(read_opt == true) {
        // TODO: Call read function
        return 0;
    } else if(write_opt == true) {
        // First check if data buffer is set
        if(data == NULL) {
            puts("Error: specify data to write into device(--help for the helper)");
            return 1;
        }
        // TODO: Call write function
        return 0;
    }

    return 0;
}