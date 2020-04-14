#ifndef TYPES_H
#define TYPES_H

#define DEFAULT_CACHE_CAPACITY 64
#define DEFAULT_SOURCE_LIMIT 8
#define DEFAULT_OUTPUT_COUNT 2

#include <string>

enum SourceType {
    Test,
    Temp,
    Volt,
    Curr,
    RPM
};

static const std::string SourceTypeLabels[] = {
    "Test",
    "Temp",
    "Volt",
    "Curr",
    "RPM"
};

enum OutputType {
    Test,
    Pi,
    XBee
};

#endif