#ifndef MULTI_DIM_VECTOR_HPP
#define MULTI_DIM_VECTOR_HPP

#include "ArrayBuilder.hpp"
#include <vector>
#include <stdexcept>

template<typename T>
class MultiDimVector 
{
private:
    std::vector<T> flat_data;
    std::vector<MultiDimVector<T>> nested_data;
    bool is_scalar = false;
    void from_builder(const ArrayBuilder<T>& builder);
    void print(int depth = 0) const;
    void flatten(std::vector<T>& result) const; // Nouvelle fonction pour aplatir

public:
    MultiDimVector();
    MultiDimVector(const ArrayBuilder<T>& builder);
    std::vector<T> array(const ArrayBuilder<T>& builder); // Remplace fonction()
    void display() const;
};

#include "MultiDimVector.tpp"
#endif