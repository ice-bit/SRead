# SRead [![Build Status](https://travis-ci.com/ice-bit/SRead.svg?branch=master)](https://travis-ci.com/ice-bit/SRead)

**S**erial**R**ead is a tool to read and write to serial ports under POSIX systems.  
To fully understand how a serial port and serial communications works under POSIX systems, please refers to [this guide.](https://www.cmrr.umn.edu/~strupp/serial.html)

## Installation
In order to install sread install GCC compiler and all the standard build utilities, then run the following:  
- `aclocal`  
- `autoconf`  
- `automake --add-missing`  
- `./configure && make`  

A binary file called `sread` will be created under `src`.

## Usage
1. Connect a device to your computer(e.g and Arduino) and retrieve his port name(e.g `/dev/ttyXXX`)  
2. Read from serial port using: `./sread -r /dev/ttyACM0 -b 9600`  
3. Write to serial port using: `./sread -w /dev/ttyACM0 -b 9600 -d <string_to_write>`  

```
SRead is a tool to read/write from/into serial ports under POSIX systems
-h, --help  | Print this helper
-r, --read  | Read from specified device/port
-w, --write | Write to specified device/port
-d, --data  | Data to write to device/port
-b, --baud  | Specify baud rate
-a, --about | About this tool
```
## Baud rates
SRead offers some common baud rates, however you cannot use a custom one, the following baud rates are supported:  
- 9600  
- 38400  
- 57600  
- 115200  
- 230400  
- 460800  

## Examples
**read example using Arduino**  
```c++
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("HIGH");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LOW");
    delay(500);
}
```
_output from `./sread -r /dev/ttyACM0 -b 9600`:_
```
HIGH
LOW
HIGH
...
```

**write example using Arduino**
```c++
String output;
void setup() {
    Serial.begin(9600);
}

void loop() {
    if(Serial.available() > 0) {
        output = Serial.readString();
        Serial.print("new message: ");
        Serial.println(output);
    }
}
```

`./sread -w /dev/ttyACM0 -b 9600 -d "hello world"`  
_output from `./sread -r /dev/ttyACM0 -b 9600`:_  
```
new message: hello world
```

## License
[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)
