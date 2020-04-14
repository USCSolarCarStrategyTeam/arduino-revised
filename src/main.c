#include "reader.h"
// #include "processor.h"
#include "writer.h"

int main(void) {
    cprintf("Reading configuration file...");

    // Read any data from files

    cprintf("Initializing telemetry system...");

    // Do any initializations
    struct Reader reader;
    // struct Processor processor;
    struct Writer writer;

    cprintf("Telemetry system active");

    while (1) {
        // read(reader);
        // process(processor);
        // write(writer);
    }
}
