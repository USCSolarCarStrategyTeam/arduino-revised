#ifndef DATA_H
#define DATA_H

class Data {
    private:
        double d_value;

    public:
        Data(const double value);
        double getValue() const;
};

#endif