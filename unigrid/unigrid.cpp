#include <iostream>
#include <vector>
#include "comdef.hpp"
#include "ring.hpp"
#include "meshbounder.hpp"


main() {
    constexpr int N = 10;
    Problem& p = *getRingProblem(2);
    std::cout << "Hello  from " << p.mBox << "\n";
    MeshBounder mb(p, N);
    mb.checkBox(p.mBox);
}
