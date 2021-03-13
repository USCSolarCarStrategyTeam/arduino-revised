#include "types.h"
#include "cache.h"

struct Input {
    enum InputType data_type;
    struct Cache data_cache;
};
