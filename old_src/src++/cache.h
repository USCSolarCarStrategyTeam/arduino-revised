#ifndef CACHE_H
#define CACHE_H

#include <data.h>
#include <string>
#include <list>
#include <types.h>

class Cache {
    private:
        std::list<Data> d_list;
        int d_capacity;

        void fitCapacity();

    public:
        Cache(const int capacity = DEFAULT_CACHE_CAPACITY);
        int getCapacity() const;
        Data getLastData() const;
        void add(const Data d);
        std::string getCacheSummary() const;
        std::string toString() const;
};

#endif