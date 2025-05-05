#ifndef INDEX_PROXY_HPP
#define INDEX_PROXY_HPP

#include <vector>
#include "MultiDimVector.hpp"

template<typename T>
class IndexProxy
{
    public:
        IndexProxy(MultiDimVector<T>& vec, std::vector<size_t> idx);
        IndexProxy(const MultiDimVector<T>& vec, std::vector<size_t> idx);
        IndexProxy<T> operator[](size_t index);
        T& operator=(const T& value);
        T& operator=(const IndexProxy<T>& other);
        operator T() const;

    private:
        MultiDimVector<T>& vec_;
        const MultiDimVector<T>& const_vec_;
        std::vector<size_t> indices_;
        bool is_const_;
};

#include "IndexProxy.tpp"
#endif
