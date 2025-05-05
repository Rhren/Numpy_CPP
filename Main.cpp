#include "MultiDimVector.hpp"
#include <iostream>

int main() 
{
    MultiDimVector<int> vec;
    MultiDimVector<std::string> vec2;

   /* auto flat = vec2.array({"hello","you"});
    auto stri = vec2.array({"coucou","hey"});
    auto s = stri + flat;
    s.print();
    flat[1] = "bon";
    flat.print();*/

    std::cout << "\n3D:" << std::endl;
    auto flat3 = vec.array({{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}});
   // std::cout << "ndim: " << flat3.ndim() << std::endl;
    flat3.print();
    flat3.shape();

    auto flat1 = vec.array({{{0, 0}, {0, 0}}, {{0, 0}, {0, 1}}});
    //auto sum = flat1 * flat3;
    flat1[0][0][1] = flat3[0][0][1];
    flat1.print();

   // sum.print();
    /*try
    {
        // Lecture
        std::cout << "flat3[0][1][0] = " << flat3[0][1][0] << std::endl; // Affiche: 3
        std::cout << "flat3[1][0][1] = " << flat3[1][0][1] << std::endl; // Affiche: 6

        // Affectation
        flat3[0][1][0] = 10; // Change 3 en 10
        flat3[1][0][1] = 23; // Change 6 en 23
        std::cout << "Après affectation:" << std::endl;
        std::cout << "flat3[0][1][0] = " << flat3[0][1][0] << std::endl; // Affiche: 10
        std::cout << "flat3[1][0][1] = " << flat3[1][0][1] << std::endl; // Affiche: 23
        flat3.print(); 
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Erreur: " << e.what() << std::endl;
    }*/
    
    /*MultiDimVector<std::string> vec1;
    auto flat =  vec1.array({"Bonjour", "le", "monde"});
    vec1.print();*/

   /* std::cout << "\n4D:" << std::endl;
    auto flat4 = vec.array({{{{{1,2},{3,4}},{{5,6},{7,8}}},{{{9,10},{11,12}},{{13,14},{15,16}}}},{{{{17,18},{19,20}},{{21,22},{23,24}}},{{{25,26},{27,28}},{{29,30},{31,32}}}}});
    vec.print();*/

    return 0;
}
