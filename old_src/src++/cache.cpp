#include <cache.h>

Cache::Cache(const int capacity) {
    if (capacity <= 0) {
        // text output
        d_capacity = DEFAULT_CACHE_CAPACITY;
    }
    else {
        d_capacity = capacity;
    }
}

int Cache::getCapacity() const {
    return d_capacity;
}

int Cache::getLastData() const {
    return d_list.back();
}

void Cache::add(const Data d) {
    d_list.push_back(d);
    fitCapacity();
}

std::string Cache::getCacheSummary() const {
    std::string summary = "";
    // Determine summary contents
    return summary;
}

std::string Cache::toString() const {
    std::string contents = "";
    // Iterate over the list and append all values to the string
    return contents;
}

void Cache::fitCapacity() {
    while (d_list.size() > d_capacity) {
        d_list.pop_front();
    }
}