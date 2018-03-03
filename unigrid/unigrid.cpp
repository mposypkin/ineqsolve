#include <iostream>
#include <vector>
#include "comdef.hpp"
#include "ring.hpp"
#include "meshbounder.hpp"
#include "ppbot.hpp"
#include "bnb.hpp"

void printBoxVec(std::vector<Box>& v) {
    for (auto & bx : v) {
        std::cout << bx << "\n";
    }
}

void printBoxVecGnuplot(int & cnt, std::vector<Box>& v, std::string color) {
    for (auto & bx : v) {
        std::cout << "set object " << cnt++ << " rect from ";
        std::cout << bx.mA[0] << ", " << bx.mA[1] << " to " << bx.mB[0] << " , " << bx.mB[1];
        std::cout << " fs solid fc rgb \'" << color << "\'\n";
        //std::cout << " fs solid noborder fc rgb \'" << color << "\'\n";
        //std::cout << " fs solid border fc rgb \'" << color << "\' lc rgb \'" << color << "\'"; 
        std::cout << std::endl;
    }
}

main() {
    constexpr int N = 10;
    //Problem& p = *getRingProblem(2);
    Problem& p = *getPPbotProblem(2);
    MeshBounder mb(p, N);

    BnB bnb(p, mb, .001);
    std::vector<Box> inv, outv, boundv;
    bnb.solve(inv, outv, boundv);
    int cnt = 1;

    std::cout << "# inner boxes:\n";
    printBoxVecGnuplot(cnt, inv, "blue");

    std::cout << "# bound boxes:\n";
    printBoxVecGnuplot(cnt, boundv, "cyan");

    std::cout << "#outer boxes:\n";
    printBoxVecGnuplot(cnt, outv, "green");

    //std::cout << "set object 15063 circle at  0,0 size 4 fs empty fc rgb'red'\n";
    //std::cout << "set object 15064 circle at  0,0 size 6 fs empty fc rgb'red'\n";
    std::cout << "set size square\n";
    std::cout << "set xrange [" << p.mBox.mA[0] << ":" << p.mBox.mB[0] << "]\n";
    std::cout << "set yrange [" << p.mBox.mA[1] << ":" << p.mBox.mB[1] << "]\n";
    std::cout << "set key off\n";
    std::cout << "plot 1/0\n";
    std::cout << "pause -1\n";

}
