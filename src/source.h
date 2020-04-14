#include "types.h"

struct Source {
    enum SourceType d_type;
    double d_cache[CACHE_CAP];
};