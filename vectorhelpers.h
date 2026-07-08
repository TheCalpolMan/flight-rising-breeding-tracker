#ifndef VECTORHELPERS_H
#define VECTORHELPERS_H

#include <vector>
#include <stdexcept>

namespace VectorHelpers
{
    template<typename T>
    int getIndex(const std::vector<T>& target, const T& value)
    {
        for (int i=0;i<target.size();i++)
        {
            if (value == target[i])
            {
                return i;
            }
        }

        throw std::invalid_argument("value does not exist");
    }
};

#endif // VECTORHELPERS_H
