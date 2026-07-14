#ifndef WEIGHTEDVALUE_H
#define WEIGHTEDVALUE_H

template<typename T>
class WeightedValue
{
public:
    unsigned long long weight;
    T value;

    WeightedValue(unsigned long long weight, const T& value) :
        weight(weight),
        value(value)
    {};
};

#endif // WEIGHTEDVALUE_H
