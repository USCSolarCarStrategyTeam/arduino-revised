#ifndef DATA_READER_H
#define DATA_READER_H

#include <types.h>
#include <string>

class DataReader {
    private:
        List<Source> d_sources;

    public:
        DataReader();
        void addSources(const SourceType type);
        std:string getMostRecent();
}

#endif
