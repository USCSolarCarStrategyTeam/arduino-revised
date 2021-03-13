#include "telemetry.h"
#include <stdio.h>


int main(void){
    cprintf("Reading configuration file...");

    // Read any data from files
    // This may include input and output types

    cprintf("Initializing telemetry system...");

    // Do any initializations
    // Keep these dynamic as long as we expect to be passing them to each other
    // Else, might just have some components be dynamic

    Reader* reader = (Reader*)malloc(sizeof(Reader));
    //Processor* processor = (Processor*)malloc(sizeof(Processor));
    Writer* writer = (Writer*)malloc(sizeof(Writer));

    cprintf("Telemetry system active");

    while (1) {
        // read(reader);
        // process(processor);
        // write(writer);
    }
    
}
