// log4arduino lightweight logging lib
// Copyright (c) 2017 by Jan Delgado
#ifndef SRC_LOG4ARDUINO_H_
#define SRC_LOG4ARDUINO_H_

#include <Arduino.h>

#ifdef ENABLE_LOG4ARDUINO
extern Print* _log4arduino_target;

extern void log4arduino_init(Print* printer);
#define LOG_INIT(p) log4arduino_init(p)

extern void log4arduino_print_head();
extern void log4arduino_debug_printf(const __FlashStringHelper* fmt, ...);

#define LOGS(s)                          \
    if (_log4arduino_target) {           \
        log4arduino_print_head();        \
        _log4arduino_target->println(s); \
    }
#define LOG(fmt, ...) log4arduino_debug_printf(F(fmt), ##__VA_ARGS__)

#else

#define LOG_INIT(p)
#define LOG(...)
#define LOGS(s)

#endif

#endif  // SRC_LOG4ARDUINO_H_
