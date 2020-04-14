#define CACHE_CAP 64
#define NUM_SOURCE 8
#define NUM_OUTPUT 2

enum SourceType {
    Test,
    Temp,
    Volt,
    Curr,
    RPM
};

static const char* SourceTypeLabels[] = {
    "Test",
    "Temp",
    "Volt",
    "Curr",
    "RPM"
};

enum OutputType {
    Test,           // For testing
    Pi,             // Raspberry Pi
    XBee            // XBee Radio Module
};

static const char* OutputLabels[] = {
    "Test",
    "Pi",
    "XBee",
};