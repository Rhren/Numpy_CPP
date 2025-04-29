#include "MultiDimVector.hpp"
#include "ArrayBuilder.hpp"
#include <iostream>

template<typename T>
MultiDimVector<T>::MultiDimVector() = default;

template<typename T>
MultiDimVector<T>::MultiDimVector(const ArrayBuilder<T>& builder) 
{
    from_builder(builder);
}
//Convertit ArrayBuilder en MultiDimVector
template<typename T>
void MultiDimVector<T>::from_builder(const ArrayBuilder<T>& builder) 
{
    if(builder.is_scalar)
    {
        flat_data = builder.flat_data;
        nested_data.clear();
        is_scalar = true;
    } 
    else
    {
        flat_data.clear();
        nested_data.clear();
        for(const auto& sub_builder : builder.nested_data) 
        {
            MultiDimVector<T> sub_vec;
            sub_vec.from_builder(sub_builder);
            nested_data.push_back(sub_vec);
        }
        is_scalar = false;
    }
}

// Nouvelle fonction pour aplatir les données
template<typename T>
void MultiDimVector<T>::flatten(std::vector<T>& result) const
{
    if(is_scalar) 
    {
        result.insert(result.end(), flat_data.begin(), flat_data.end());
    } 
    else 
    {
        for(const auto& sub_vec : nested_data) 
        {
            sub_vec.flatten(result);
        }
    }
}

template<typename T>
std::vector<T> MultiDimVector<T>::array(const ArrayBuilder<T>& builder) 
{
    from_builder(builder);
    std::vector<T> result;
    flatten(result);
    return result;
}

template<typename T>
void MultiDimVector<T>::print(int depth) const
{
    if (is_scalar) 
    {
        for (const auto& item : flat_data) 
        {
            for (int i = 0; i < depth; ++i) std::cout << "  ";
            std::cout << item << std::endl;
        }
    } 
    else 
    {
        for (const auto& sub_vec : nested_data) 
        {
            for (int i = 0; i < depth; ++i) std::cout << "  ";
            std::cout << "{" << std::endl;
            sub_vec.print(depth + 1);
            for (int i = 0; i < depth; ++i) std::cout << "  ";
            std::cout << "}" << std::endl;
        }
    }
}

template<typename T>
void MultiDimVector<T>::display() const 
{
    std::cout << "MultiDimVector:" << std::endl;
    print();
}