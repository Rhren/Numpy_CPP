#ifndef MULTI_DIM_VECTOR_HPP
#define MULTI_DIM_VECTOR_HPP

#include <vector>
#include <iostream>
#include "ArrayBuilder.hpp"
#include "IndexProxy.hpp"

template<typename T>
class MultiDimVector
{
    public:
        MultiDimVector();
        MultiDimVector(const ArrayBuilder<T>& builder);

        // Méthodes existantes...
        void from_builder(const ArrayBuilder<T>& builder);
        void display(std::ostream& os = std::cout, int depth = 0) const;
        void print() const;
        size_t ndim() const;
        std::vector<size_t> get_shape() const;
        void shape() const;
        void flatten(std::vector<T>& flat) const;
        MultiDimVector<T> array(const ArrayBuilder<T>& builder);
        MultiDimVector<T> reshape(const MultiDimVector<T>& input, const std::vector<size_t>& new_shape);

        // Indexation
        IndexProxy<T> operator[](size_t index);
        const IndexProxy<T> operator[](size_t index) const;

        // Nouveaux opérateurs pour les opérations arithmétiques
        MultiDimVector<T> operator+(const MultiDimVector<T>& other) const;
        MultiDimVector<T> operator-(const MultiDimVector<T>& other) const;
        MultiDimVector<T> operator*(const MultiDimVector<T>& other) const;

        // Données membres
        std::vector<T> flat_data;
        std::vector<MultiDimVector<T>> nested_data;
        std::vector<size_t> original_shape;
        bool is_scalar;

        // Accès interne pour IndexProxyr
        T& get_element(const std::vector<size_t>& indices);
        const T& get_element(const std::vector<size_t>& indices) const;
        void set_element(const std::vector<size_t>& indices, const T& value);

    private:
        void check_compatible_shapes(const std::vector<size_t>& shape1, const std::vector<size_t>& shape2) const;
};

#include "MultiDimVector.tpp"

#endif
