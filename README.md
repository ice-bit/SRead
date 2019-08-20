# SRead

**S**erial**R**ead is a tool to read and write to serial ports under POSIX systems.  
To fully understand how a serial port and serial communications works under POSIX systems, please refers to [this guide.](https://www.cmrr.umn.edu/~strupp/serial.html)

## Installation
Before compiling it be sure to install the following dependencies:  
- C++14  
- Boost libraries  
- CMake

```bash
mkdir build
cd build
cmake .. && make
```

## Usage
1. Connect a device to your computer(e.g and Arduino) and retrieve his port name(e.g `/dev/ttyXXX`)  
2. Read from serial port using: `./sread -r /dev/ttyACM0 -b 9600 -e false`  
3. Write to serial port using: `./sread -w /dev/ttyACM0 -b 9600 -e false -d <string_to_write>`  

```
SRead is a tool to read/write from/into serial ports under POSIX systems

Allowed options:
  -h [ --help ]         Print the helper
  -r [ --read ] arg     Read from device/port
  -w [ --write ] arg    Write to device/port
  -d [ --data ] arg     Data to write to device/port
  -b [ --baud ] arg     Specify baud rate
  -e [ --echo ] arg     Enable/Disable echo mode
  -a [ --about ]        About this tool
```
## Baud rates
SRead offers some common baud rates, however you cannot use a custom one, the following baud rates are supported:  
- 9600  
- 38400  
- 57600  
- 115200

## Echo mode
Echo mode can be enabled or disabled using the `--echo,-e` flag, however this should not change the behavior of the tool since [canonical mode](https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html) is always disabled.

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
_output from `./sread -r /dev/ttyACM0 -b 9600 -e false`:_
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

`./sread -w /dev/ttyACM0 -b 9600 -e false -d "hello world"`  
_output from `./sread -r /dev/ttyACM0 -b 9600 -e false`:_  
```
new message: hello world
```

## License
[GPLv3](https://choosealicense.com/licenses/gpl-3.0/)