#include "IndexProxy.hpp"

template<typename T>
IndexProxy<T>::IndexProxy(MultiDimVector<T>& vec, std::vector<size_t> idx)
    : vec_(vec), const_vec_(vec), indices_(idx), is_const_(false) 
{
}

template<typename T>
IndexProxy<T>::IndexProxy(const MultiDimVector<T>& vec, std::vector<size_t> idx)
    : vec_(const_cast<MultiDimVector<T>&>(vec)), const_vec_(vec), indices_(idx), is_const_(true)
{
}

template<typename T>
IndexProxy<T> IndexProxy<T>::operator[](size_t index)
{
    std::vector<size_t> new_indices = indices_;
    new_indices.push_back(index);
    return IndexProxy<T>(vec_, new_indices);
}

template<typename T>
T& IndexProxy<T>::operator=(const T& value)
{
    if(is_const_) 
    {
        throw std::runtime_error("Cannot assign to const IndexProxy");
    }
    vec_.set_element(indices_, value);
    return vec_.get_element(indices_);
}

template<typename T>
T& IndexProxy<T>::operator=(const IndexProxy<T>& other) {
    if (is_const_) {
        throw std::runtime_error("Cannot assign to const IndexProxy");
    }
    // Convertir l'autre IndexProxy en T et l'assigner
    T value = static_cast<T>(other); // Utilise l'opérateur de conversion operator T()
    vec_.set_element(indices_, value);
    return vec_.get_element(indices_);
}

template<typename T>
IndexProxy<T>::operator T() const
{
    return const_vec_.get_element(indices_);
}