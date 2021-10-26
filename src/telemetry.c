#include "telemetry.h"
#include <stdio.h>
#include "cache.h"
#include "types.h"

void read(enum InputType* t, int n);
void process(unsigned int raw, enum InputType t);
void write(enum InputType* t, cache**, int n, char* filename);
// int getRaw(enum InputType t);
// this function takes input type and gets analog value from correct pins
// pins can be defined at top of file

int main(void){
    // declare major variables
    unsigned int numInputs;
    enum InputType* inTypes;
    cache** dataCache;

    cprintf("Reading configuration file...");

    // Read any data from files
    // This may include input and output types
    FILE* fp = fopen("config.txt", "r");
    fscanf(fp, "%u", numInputs); // read number of input types

    // initialize array of input types and caches
    inTypes = (enum InputType*) malloc(numInputs*sizeof(enum InputType));

    for(unsigned int i = 0; i < numInputs; i++) { // read input types
        char fileBuff[20];
        fscanf(fp, "%s", fileBuff);
        inTypes = str2enum(fileBuff);
    }
    fclose(fp);

    cprintf("Initializing telemetry system...");

    // Do any initializations
    // Keep these dynamic as long as we expect to be passing them to each other
    // Else, might just have some components be dynamic

    //Reader* reader = (Reader*)malloc(sizeof(Reader));
    //Processor* processor = (Processor*)malloc(sizeof(Processor));
    //Writer* writer = (Writer*)malloc(sizeof(Writer));

    // init caches for each data type
    // init array of cache pointers
    dataCache = (cache**) malloc(numInputs*sizeof(cache*))
    for(unsigned int i = 0; i < numInputs; i++) {
        dataCache[i] = cache_init();
    }

    cprintf("Telemetry system active");

    while (1) {
        // read(reader);
        // process(processor);
        // write(writer);
        read(inTypes, numInputs);
        write(inTypes, dataCache, numInputs, "data.txt");
    }

}

void read(enum InputType* t, int n) {
    int raw;
    for(int i = 0; i < n; i++) {
        // if there is a unified way to read diff input types
        // (ie. raw = getRaw(t[i]));
        // can this if chain and replace with
        // insert(dataCache[i], process(raw, t[i]));
        if(t[i] == Temp) {
            // read temp
            insert(dataCache[i], process(raw, Temp));
        } else if(t[i] == Volt) {
            // read volt
            insert(dataCache[i], process(raw, Volt));
        } else if(t[i] == Curr) {
            // read curr
            insert(dataCache[i], process(raw, Curr));
        } else if(t[i] == RPM) {
            // read rpm
            insert(dataCache[i], process(raw, RPM));
        }
    }
}

void process(unsigned int raw, enum InputType t) {
    if(t[i] == Temp) {
        // process temp
        return raw;
    } else if(t[i] == Volt) {
        // process volt
        return raw;
    } else if(t[i] == Curr) {
        // process curr
        return raw;
    } else if(t[i] == RPM) {
        // process rpm
        return raw;
    }
}

void write(enum InputType* t, cache** c, int n, char* filename) {
    FILE* fp = fopen(filename, "w"); // open file for writing
                                     // will create new file if doesn't exist
    for(int i = 0; i < n; i++) {
        fprintf(fp, "%4.4s : %d", t[i], c[i]->head->data);
    }
    fclose(fp);
}
