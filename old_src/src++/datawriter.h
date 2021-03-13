#ifndef DATA_WRITER_H
#define DATA_WRITER_H

#include <types.h>
#include <output.h>

class DataWriter {
    private:
        List<Output> d_outputs;
    
    public:
        DataWriter();
        void addOutput(const OutputType type);
}

#endif