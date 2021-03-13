#ifndef SOURCE_H
#define SOURCE_H

#include <types.h>
#include <list>

class Source {
    private:
        LinkedList<Data> d_cache;
        SourceType d_type;

    public:
        Data getNewest() const;
        void pushToCache(const Data d);
        Source(const SourceType type, const double capacity);

        string getCacheStatus() const;
        string printCache() const;
        SourceType getSourceType() const;
};

#endif