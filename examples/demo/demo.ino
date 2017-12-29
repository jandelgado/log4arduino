// log4arduino lightweight logging lib
// Copyright (c) 2017 by Jan Delgado
#define ENABLE_LOG4ARDUINO
#include <log4arduino.h>

void setup() {
    Serial.begin(9600);
    LOG_INIT(&Serial);

    // use LOG() for printf-like logging
    LOG("hello, log4arduino.");
    LOG("use %s formatting: %d %c %d %c %d", "printf", 9, '+', 1, '=', 10);
    constexpr uint32_t magic = 3735928559;
    LOG("hex output: %lu == 0x%lX", magic, magic);

    // use LOGS() for simple logging of single arguments
    const char *pStr = "some string from RAM";
    LOGS(pStr);
    LOGS(F("this string is stored in flash memory"));
    LOGS(String("some String object"));
    LOGS(123);
}

void loop() { }


