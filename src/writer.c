#include "writer.h"

int write(struct Writer* writer) {
    int i;
    for (i = 0; i < N_OUTPUT; i++) {
        struct Output* output = writer->d_outputs[i];
        if (output) {
            // Export data to output
        }
    }
    return 0;
}