#include <iostream>
#include <vector>
#include "comdef.hpp"
#include "ring.hpp"


main() {
    
    Problem& p = *getRingProblem(2);
    std::cout << "Hello  from " << p.mBox << "\n";
}
