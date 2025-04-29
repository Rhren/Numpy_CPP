#include "MultiDimVector.hpp"
#include <iostream>

int main() 
{
    MultiDimVector<int> vec;
    // Tests avec différentes dimensions
    std::cout << "1D:" << std::endl;
    auto flat1 = vec.array({1, 2, 3});
    for(const auto& val : flat1) std::cout << val << " ";
    std::cout << std::endl;

    std::cout << "\n2D:" << std::endl;
    auto flat2 = vec.array({{1, 2}, {3, 4}});
    for (const auto& val : flat2) std::cout << val << " ";
    std::cout << std::endl;

    std::cout << "\n3D:" << std::endl;
    auto flat3 = vec.array({{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}});
    for (const auto& val : flat3) std::cout << val << " ";
    std::cout << std::endl;

    std::cout << "\n4D:" << std::endl;
    auto flat4 = vec.array({{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}}, {{{9, 10}, {11, 12}}, {{13, 14}, {15, 16}}}});
    for (const auto& val : flat4) std::cout << val << " ";
    std::cout << std::endl;

    // Test avec une taille non uniforme (lève une exception)
    try 
    {
        std::cout << "\n2D (invalide):" << std::endl;
        auto flat_invalid = vec.array({{1, 2}, {3}});
        for (const auto& val : flat_invalid) std::cout << val << " ";
        std::cout << std::endl;
    } 
    catch (const std::exception& e) 
    {
        std::cout << "Erreur: " << e.what() << std::endl;
    }

    return 0;
}