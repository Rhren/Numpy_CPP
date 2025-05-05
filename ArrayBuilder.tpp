#include "ArrayBuilder.hpp"
#include <vector>
#include <initializer_list>
#include <string>
#include <stdexcept>

template<typename T>
ArrayBuilder<T>::ArrayBuilder(const std::initializer_list<T>& list)
{
    flat_data = list;
    nested_data.clear();
    is_scalar = true;
    if (flat_data.empty()) {
        throw std::invalid_argument("ArrayBuilder: empty initializer list for flat data");
    }
}

template<typename T>
ArrayBuilder<T>::ArrayBuilder(const std::initializer_list<ArrayBuilder<T>>& list)
{
    nested_data = list;
    flat_data.clear();
    is_scalar = false;
    if(nested_data.empty()) 
    {
        throw std::invalid_argument("ArrayBuilder: empty initializer list for nested data");
    }
    validate_uniform_size(nested_data);
}

template<typename T>
template<typename U>
void ArrayBuilder<T>::validate_uniform_size(const std::vector<ArrayBuilder<U>>& vec) const
{
    if (vec.empty()) {
        return;
    }
    size_t expected_size = vec[0].is_scalar ? vec[0].flat_data.size() : vec[0].nested_data.size();
    for (size_t i = 1; i < vec.size(); ++i) {
        size_t current_size = vec[i].is_scalar ? vec[i].flat_data.size() : vec[i].nested_data.size();
        if (current_size != expected_size) {
            throw std::invalid_argument("ArrayBuilder: non-uniform size in nested data");
        }
        if (!vec[i].is_scalar) {
            validate_uniform_size(vec[i].nested_data);
        }
    }
}
