# log4arduino

A lightweight, no-frills logging library for Arduino & friends.

* simple interface - just three macros
* printf-like formatting
* each log entry is prepended by timestamp and amount of avail free RAM
* automatically uses flash memory to save SRAM (if supported)
* log target can be any subclass of class `Printer`, e.g. class `Serial`
* zero memory footprint when turned off

## Example

```c++
#define ENABLE_LOG4ARDUINO
#include <log4arduino.h>

void setup() {
    Serial.begin(9600);
    LOG_INIT(&Serial);

    // use LOG() for printf-like logging
    LOG("hello, log4arduino.");
    LOG("use %s formatting: %d+%d=%0x02d", "printf", 9, 1, 10);

    // use LOGS() for simple logging of single arguments
    const char *pStr = "some string";
    LOGS(pStr);
    LOGS(String("some string object"));
    LOGS(123);
}

void loop() { }
```

will print out the following on the `Serial` interface:

```
0(1623): hello, log4arduino.
0(1609): use printf formatting: 9 + 1 = 10
9(1599): hex output: 3735928559 == 0xDEADBEEF
58(1695): some string from RAM
91(1695): this string is stored in flash memory
142(1695): some String object
174(1695): 123
```

The actual log messages are preceeded by the current time as returned by
`millis()` as well as the free heap space, e.g. `91(1695):`.

## API

### Header

To use log4arduino, define `ENABLE_LOG4ARDUINO` and include the `log4arduino.h`
header.  If `ENABLE_LOG4ARDUINO` is not defined, then logging will be disabled
(and not compiled in). This is what you typically want in a release build.

### Logging interface

3 Macros are used for logging: `LOG_INIT`, `LOG` and `LOGS`:

#### LOG_INIT

The `LOG_INIT(target)` macro initializes the logging. It takes a pointer to a
subclass of the [Print](https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.h)
class as argument, which specifies the log target, e.g. `LOG_INIT(&Serial)`. No
logging will happen until `LOG_INIT` is called. If needed, call
`LOG_INIT(nullptr)` to turn off logging during runtime.

#### LOG(fmt, ...)

Use the `LOG(fmt, ...)` macro to log in a
[printf-like](http://www.cplusplus.com/reference/cstdio/printf/) fashion. The
`fmt` format string will automatically be stored in flash memory using the
`F()` macro to reduce amount of SRAM being used.

#### LOGS(s)

Use the `LOGS(s)` (the *S* stands for *simple*) macro, to directly log out the
given value using the log target's `print` method.

## A word on log levels

log4arduino does not support log levels. This lib is not meant for enterprise
development and we have to keep the memory footprint low. YAGNI.

## Author

Jan Delgado

## License

MIT
