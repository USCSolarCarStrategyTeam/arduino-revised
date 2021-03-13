#include "reader.h"
#include "processor.h"
#include "writer.h"

int main(void) {
    cprintf("Reading configuration file...");

    // Read any data from files
    // This may include input and output types

    cprintf("Initializing telemetry system...");

    // Do any initializations
    // Keep these dynamic as long as we expect to be passing them to each other
    // Else, might just have some components be dynamic

    struct Reader* reader = (struct Reader*)malloc(sizeof(struct Reader));
    struct Processor* processor = (struct Processor*)malloc(sizeof(struct Processor));
    struct Writer* writer = (struct Writer*)malloc(sizeof(struct Writer));

    cprintf("Telemetry system active");

    while (1) {
        // read(reader);
        // process(processor);
        // write(writer);
    }
}
