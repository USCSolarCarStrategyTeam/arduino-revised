#include <data.h>

Data::Data(const double value) {
    d_value = value;
}

double Data::getValue() const {
    return d_value;
}