enum InputType {
    Test,
    Temp,
    Volt,
    Curr,
    RPM
};

static const char* InputLabels[] = {
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
