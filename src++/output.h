#ifndef OUTPUT_H
#define OUTPUT_H

class Output {
    private:
        OutputType d_type;

    public:
        abstract void writeToDevice();
}

#endif