#define N_IN_TYPES 4
#define N_OUT_TYPES 3;

enum InputType {
    Temp,
    Volt,
    Curr,
    RPM
};

static const char* InputLabels[N_IN_TYPES] = {
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

static const char* OutputLabels[N_OUT_TYPES] = {
    "Test",
    "Pi",
    "XBee",
};

enum InputType* str2enum(char*);
