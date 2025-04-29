#include "ArrayBuilder.hpp"

template<typename T>
template<typename U>
void ArrayBuilder<T>::validate_uniform_size(const std::vector<ArrayBuilder<U>>& vec) const 
{
    if(vec.empty()) return;
    size_t expected_size = vec[0].is_scalar ? vec[0].flat_data.size() : vec[0].nested_data.size();
    for (const auto& sub_vec : vec) {
        size_t current_size = sub_vec.is_scalar ? sub_vec.flat_data.size() : sub_vec.nested_data.size();
        if (current_size != expected_size) {
            throw std::invalid_argument("Toutes les sous-listes doivent avoir la même taille");
        }
    }
}

template<typename T>
ArrayBuilder<T>::ArrayBuilder(const std::initializer_list<T>& list) : flat_data(list), is_scalar(true) {}

template<typename T>
ArrayBuilder<T>::ArrayBuilder(const std::initializer_list<ArrayBuilder<T>>& list) : nested_data(list), is_scalar(false) 
{
    validate_uniform_size(nested_data);
}


