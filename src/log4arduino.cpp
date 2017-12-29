// log4arduino lightweight logging lib
// Copyright (c) 2017 by Jan Delgado
#include "log4arduino.h"    // NOLINT

#ifndef LOG_MAX_STRING_LEN
#define LOG_MAX_STRING_LEN 64
#endif

// workaround for frameworks which don't have PROGMEM support and don't
// set the vnsprintf_P macro (e.g. avrsam). We assume that if sprintf_P
// is defined, then there is no PROGMEM support, cause otherwise there
// would be a function of that name.
// TODO(JD) build check using PROGMEM
#if !defined(sprintf_P)
#define vsnprintf vsnprintf_P
#endif

Print* _log4arduino_target = nullptr;

// deterine free heap memory. platform dependent.
static int free_ram() {
#if defined(ESP8266) || defined(ESP32)
    return ESP.getFreeHeap();
#elif defined(AVR)
    // taken from
    // https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
    extern uintptr_t __heap_start;
    extern void *__brkval;
    intptr_t v;
    return (uintptr_t)&v -
           (__brkval == 0 ? (uintptr_t)&__heap_start : (uintptr_t)__brkval);
#else
    return 0;
#endif
}

void log4arduino_init(Print* printer) { _log4arduino_target = printer; }

// print the line header with time and free ram, e.g. "12345(1234): "
void log4arduino_print_head() {
    if (!_log4arduino_target) {
        return;
    }
    char buf[LOG_MAX_STRING_LEN];
    const auto fmt = F("%ld(%d): ");
    sprintf_P(buf, (PGM_P)fmt, millis(), free_ram());
    _log4arduino_target->print(buf);
}

// printf-like formatted logging.
void log4arduino_debug_printf(const __FlashStringHelper* fmt, ...) {
    if (!_log4arduino_target) {
        return;
    }
    char buf[LOG_MAX_STRING_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, LOG_MAX_STRING_LEN, (PGM_P)fmt, args);
    va_end(args);
    log4arduino_print_head();
    _log4arduino_target->println(buf);
}
