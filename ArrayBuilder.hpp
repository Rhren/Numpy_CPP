
#ifndef ARRAY_BUILDER_HPP
#define ARRAY_BUILDER_HPP

#include <vector>
#include <stdexcept>

template<typename U> class MultiDimVector;
template<typename T>
class ArrayBuilder 
{
    private:
        std::vector<T> flat_data;
        std::vector<ArrayBuilder<T>> nested_data;
        bool is_scalar = false;

        template<typename U>
        void validate_uniform_size(const std::vector<ArrayBuilder<U>>& vec) const;

    public:
        ArrayBuilder(const std::initializer_list<T>& list);
        ArrayBuilder(const std::initializer_list<ArrayBuilder<T>>& list);

        // Forward declaration of MultiDimVector as friend
        template<typename U> friend class MultiDimVector;
};

#include "ArrayBuilder.tpp"

#endif // ARRAY_BUILDER_HPP