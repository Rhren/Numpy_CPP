#include "MultiDimVector.hpp"
#include <iostream>

int main() 
{
    MultiDimVector<int> vec;
    // Tests avec différentes dimensions
   // std::cout << "1D:" << std::endl;
   // auto flat1 = vec.array({1, 2, 3});
   // vec.print();
    //std::cout << "ndim: " << flat1.ndim() << std::endl;
   // flat1.ndim();

    //std::cout << "\n2D:" << std::endl;
   // auto flat2 = vec.array({{1, 2}, {3, 4}});
   // vec.print();
    //std::cout << "ndim: " << flat2.ndim() << std::endl;
   // flat2.ndim();

    std::cout << "\n3D:" << std::endl;
    auto flat3 = vec.array({{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}});
   // std::cout << "ndim: " << flat3.ndim() << std::endl;
    vec.print();
    flat3.shape();
    vec.print();

        // Accès et affectation avec value()
        std::cout << "\nAccès et affectation avec value():" << std::endl;
        try
        {
            // Lecture
            std::cout << "flat3.value({0, 1, 0}) = " << flat3.value({0, 1, 0}) << std::endl; // Affiche: 3
            std::cout << "flat3.value({1, 0, 1}) = " << flat3.value({1, 0, 1}) << std::endl; // Affiche: 6
            // Affectation
            flat3.value({0, 1, 0}) = 10; // Change 3 en 10
            flat3.value({1, 0, 1}) = 23; // Change 6 en 23
            std::cout << "Après affectation:" << std::endl;
            std::cout << "flat3.value({0, 1, 0}) = " << flat3.value({0, 1, 0}) << std::endl; // Affiche: 10
            std::cout << "flat3.value({1, 0, 1}) = " << flat3.value({1, 0, 1}) << std::endl; // Affiche: 23
            flat3.print(); // Affiche: array([[[1, 2], [10, 4]], [[5, 23], [7, 8]]])
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "Erreur: " << e.what() << std::endl;
        }
        

    //flat3 = vec.reshape(flat3,{7});
    /* try
    {
        flat3 = vec.reshape(flat3, {7}); // Forme incompatible
        flat3.shape();
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Erreur: " << e.what() << std::endl;
    }*/
   
    /*MultiDimVector<std::string> vec1;
    auto flat =  vec1.array({"Bonjour", "le", "monde"});
    vec1.print();*/

   /* std::cout << "\n4D:" << std::endl;
    auto flat4 = vec.array({{{{{1,2},{3,4}},{{5,6},{7,8}}},{{{9,10},{11,12}},{{13,14},{15,16}}}},{{{{17,18},{19,20}},{{21,22},{23,24}}},{{{25,26},{27,28}},{{29,30},{31,32}}}}});
    vec.print();*/

    // Test avec une taille non uniforme (lève une exception)
    /*try 
    {
        std::cout << "\n2D (invalide):" << std::endl;
        auto flat_invalid = vec.array({{1, 2}, {3}});
        for (const auto& val : flat_invalid) std::cout << val << " ";
        std::cout << std::endl;
    } 
    catch (const std::exception& e) 
    {
        std::cout << "Erreur: " << e.what() << std::endl;
    }*/

    return 0;
}
