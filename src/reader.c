#include "reader.h"

int read(struct Reader* reader) {
    int i;
    for (i = 0; i < N_INPUT; i++) {
        struct Input* input = reader->d_inputs[i];
        if (input) {
            // Extract data from input
        }
    }
}
