#include "defs.h"
#include "types.h"

struct Input {
    enum InputType d_type;
    double d_cache[CACHE_CAP];
};
