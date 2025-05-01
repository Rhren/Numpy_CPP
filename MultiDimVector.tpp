#include "MultiDimVector.hpp"
#include "ArrayBuilder.hpp"
#include <iostream>
#include <numeric>
#include <sstream>

template<typename T>
MultiDimVector<T>::MultiDimVector() : is_scalar(false) {}

template<typename T>
MultiDimVector<T>::MultiDimVector(const ArrayBuilder<T>& builder) 
{
    from_builder(builder);
}

template<typename T>
void MultiDimVector<T>::from_builder(const ArrayBuilder<T>& builder) 
{
    if (builder.is_scalar)
    {
        flat_data = builder.flat_data;
        nested_data.clear();
        is_scalar = true;
        original_shape = {flat_data.size()};
    } 
    else
    {
        flat_data.clear();
        nested_data.clear();
        original_shape.clear();
        original_shape.push_back(builder.nested_data.size());
        if (!builder.nested_data.empty()) 
        {
            MultiDimVector<T> sub_vec(builder.nested_data[0]);
            auto sub_shape = sub_vec.get_shape();
            original_shape.insert(original_shape.end(), sub_shape.begin(), sub_shape.end());
            for (const auto& sub_builder : builder.nested_data) 
            {
                MultiDimVector<T> sub_vec;
                sub_vec.from_builder(sub_builder);
                nested_data.push_back(sub_vec);
            }
        }
        is_scalar = false;
    }
}

template<typename T>
MultiDimVector<T> MultiDimVector<T>::array(const ArrayBuilder<T>& builder) 
{
    MultiDimVector<T> result;
    result.from_builder(builder);
    return result;
}

template<typename T>
T& MultiDimVector<T>::value(const std::vector<size_t>& indices)
{
    return get_element(indices);
}

template<typename T>
const T& MultiDimVector<T>::value(const std::vector<size_t>& indices) const
{
    return get_element(indices);
}

template<typename T>
T& MultiDimVector<T>::get_element(const std::vector<size_t>& indices)
{
    if (indices.empty())
    {
        throw std::out_of_range("IndexError: too few indices for array");
    }

    if (is_scalar)
    {
        if (indices.size() != 1)
        {
            throw std::out_of_range("IndexError: too many indices for scalar array");
        }
        if (indices[0] >= flat_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << flat_data.size();
            throw std::out_of_range(ss.str());
        }
        return flat_data[indices[0]];
    }
    else
    {
        if (indices[0] >= nested_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << nested_data.size();
            throw std::out_of_range(ss.str());
        }
        std::vector<size_t> sub_indices(indices.begin() + 1, indices.end());
        return nested_data[indices[0]].get_element(sub_indices);
    }
}

template<typename T>
const T& MultiDimVector<T>::get_element(const std::vector<size_t>& indices) const
{
    if (indices.empty())
    {
        throw std::out_of_range("IndexError: too few indices for array");
    }

    if (is_scalar)
    {
        if (indices.size() != 1)
        {
            throw std::out_of_range("IndexError: too many indices for scalar array");
        }
        if (indices[0] >= flat_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << flat_data.size();
            throw std::out_of_range(ss.str());
        }
        return flat_data[indices[0]];
    }
    else
    {
        if (indices[0] >= nested_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << nested_data.size();
            throw std::out_of_range(ss.str());
        }
        std::vector<size_t> sub_indices(indices.begin() + 1, indices.end());
        return nested_data[indices[0]].get_element(sub_indices);
    }
}

template<typename T>
void MultiDimVector<T>::set_element(const std::vector<size_t>& indices, const T& value)
{
    if (indices.empty())
    {
        throw std::out_of_range("IndexError: too few indices for array");
    }

    if (is_scalar)
    {
        if (indices.size() != 1)
        {
            throw std::out_of_range("IndexError: too many indices for scalar array");
        }
        if (indices[0] >= flat_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << flat_data.size();
            throw std::out_of_range(ss.str());
        }
        flat_data[indices[0]] = value;
    }
    else
    {
        if (indices[0] >= nested_data.size())
        {
            std::ostringstream ss;
            ss << "IndexError: index " << indices[0] << " is out of bounds for axis 0 with size " << nested_data.size();
            throw std::out_of_range(ss.str());
        }
        std::vector<size_t> sub_indices(indices.begin() + 1, indices.end());
        nested_data[indices[0]].set_element(sub_indices, value);
    }
}

template<typename T>
void MultiDimVector<T>::display(std::ostream& os, int depth) const
{
    std::string indent(depth * 2, ' ');
    os << indent << "[";

    if (is_scalar)
    {
        if (flat_data.empty())
        {
            os << "empty";
        }
        else
        {
            for (size_t i = 0; i < flat_data.size(); ++i)
            {
                os << flat_data[i];
                if (i < flat_data.size() - 1)
                {
                    os << ", ";
                }
            }
        }
    }
    else
    {
        if (nested_data.empty())
        {
            os << "empty";
        }
        else
        {
            os << "\n";
            for (size_t i = 0; i < nested_data.size(); ++i)
            {
                nested_data[i].display(os, depth + 1);
                if (i < nested_data.size() - 1)
                {
                    os << ",";
                }
                os << "\n";
            }
            os << indent;
        }
    }
    os << "]";
}

template<typename T>
void MultiDimVector<T>::print() const 
{
    display(std::cout, 0);
    std::cout << std::endl;
}

template<typename T>
size_t MultiDimVector<T>::ndim() const
{
    return original_shape.size();
}

template<typename T>
std::vector<size_t> MultiDimVector<T>::get_shape() const
{
    return original_shape;
}

template<typename T>
void MultiDimVector<T>::shape() const
{
    std::cout << "(";
    for (size_t i = 0; i < original_shape.size(); ++i)
    {
        std::cout << original_shape[i];
        if (i < original_shape.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << ")" << std::endl;
}

template<typename T>
void MultiDimVector<T>::flatten(std::vector<T>& result) const
{
    if (is_scalar) 
    {
        result.insert(result.end(), flat_data.begin(), flat_data.end());
    } 
    else 
    {
        for (const auto& sub_vec : nested_data) 
        {
            sub_vec.flatten(result);
        }
    }
}

template<typename T>
MultiDimVector<T> MultiDimVector<T>::reshape(const MultiDimVector<T>& input, const std::vector<size_t>& new_shape)
{
    std::vector<T> flat;
    input.flatten(flat);
    size_t total_size = std::accumulate(new_shape.begin(), new_shape.end(), size_t(1), std::multiplies<size_t>());
    
    if (total_size != flat.size())
    {
        std::ostringstream ss;
        ss << "ValueError: cannot reshape array of size " << flat.size() << " into shape (";
        for (size_t i = 0; i < new_shape.size(); ++i)
        {
            ss << new_shape[i];
            if (i < new_shape.size() - 1)
            {
                ss << ",";
            }
        }
        ss << ")";
        throw std::invalid_argument(ss.str());
    }

    MultiDimVector<T> result;
    result.original_shape = new_shape;
    result.flat_data.clear();
    result.nested_data.clear();
    result.is_scalar = false;
    
    if (new_shape.size() == 1)
    {
        result.flat_data = flat;
        result.is_scalar = true;
        result.print();
        return result;
    }

    std::vector<size_t> sub_shape(new_shape.begin() + 1, new_shape.end());
    size_t sub_size = std::accumulate(sub_shape.begin(), sub_shape.end(), size_t(1), std::multiplies<size_t>());
    size_t offset = 0;
    
    result.nested_data.resize(new_shape[0]);
    
    for (size_t i = 0; i < new_shape[0]; ++i)
    {
        MultiDimVector<T> sub_vec;
        
        if (sub_shape.size() == 1)
        {
            sub_vec.flat_data.assign(flat.begin() + offset, flat.begin() + offset + sub_shape[0]);
            sub_vec.is_scalar = true;
            sub_vec.original_shape = {sub_shape[0]};
        }
        else
        {
            MultiDimVector<T> temp;
            temp.flat_data.assign(flat.begin() + offset, flat.begin() + offset + sub_size);
            temp.is_scalar = true;
            temp.original_shape = {sub_size};
            sub_vec = reshape(temp, sub_shape);
        }
        result.nested_data[i] = sub_vec;
        offset += sub_size;
    }
    
    result.print();
    return result;
}
