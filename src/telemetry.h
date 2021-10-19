#include "types.h"
#define CACHE_CAP 64        // Capacity of each Input cache
#define N_INPUT 8           // Number of Input types a Reader stores
#define N_OUTPUT 3          // Number of Output types a Writer stores

typedef struct Input {
    enum InputType data_type;
    Cache data_cache;
} Input;

typedef struct Output {
    enum OutputType d_type;
} Output;

typedef struct Reader {
    Input* d_inputs[N_INPUT];
} Reader;

/*typedef struct Processor {

} Processor;*/

typedef struct Writer {
    Output* d_outputs[N_OUTPUT];
} Writer;
