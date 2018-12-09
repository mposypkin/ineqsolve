#include <iostream>
#include <vector>
#include <string>
#include "comdef.hpp"
#include "bnb.hpp"
#include "meshbnd.hpp"
#include "lipbnd.hpp"
#include "simpsort.hpp"
#include "ring.hpp"
#include "ppbot.hpp"
#include "ringseq.hpp"
#include "rbot.hpp"
#include "rbotineq.hpp"
#include "rpr.hpp"

void printBoxVec(std::vector<Box>& v) {
	for (auto & bx : v) {
		std::cout << bx << "\n";
	}
}

void printBoxVecGnuplot(int & cnt, std::vector<Box>& v, std::string color) {
	for (auto & bx : v) {
		std::cout << "set object " << cnt++ << " rect from ";
		std::cout << bx.mA[0] << ", " << bx.mA[1] << " to " << bx.mB[0] << " , "
				<< bx.mB[1];
		std::cout << " fs solid fc rgb \'" << color << "\'\n";
		//std::cout << " fs solid noborder fc rgb \'" << color << "\'\n";
		//std::cout << " fs solid border fc rgb \'" << color << "\' lc rgb \'" << color << "\'";
		std::cout << std::endl;
	}
}

void printBoxVecJSON(int & cnt, std::vector<Box>& v) {
	constexpr int n = 3;
	FT center[n];
	std::cout << "[";
	bool comma = false;
	for (auto & bx : v) {
		bx.getCenter(center);
		if (comma)
			std::cout << ", ";
		else
			comma = true;
		std::cout << "{";
		std::cout << "x_center: " << center[0] << ", ";
		std::cout << "y_center: " << center[1] << ", ";
		std::cout << "z_center: " << center[2] << ", ";
		std::cout << "w: " << bx.mB[0] - bx.mA[0] << ", ";
		std::cout << "h: " << bx.mB[1] - bx.mA[1] << ", ";
		std::cout << "d: " << bx.mB[2] - bx.mA[2];
		std::cout << "}";
	}
	std::cout << "]\n";
}

int main(int argc, char* argv[]) {
	constexpr int npoints = 8;
	constexpr FT eps = 1e-1;
	int nt = 0;
	const char* help = "usage: \n serial run: \n\t\t unigrid.exe \n parallel run: \n\t unigrid.exe <number_of_threads>\n";
	if (argc == 2) {
		if(std::string(argv[1]) == std::string("-h")) {
			std::cout << help;
			exit(0);
		}
		nt = atoi(argv[1]);
	}
	//Problem& p = *getRingProblem(2);
//	 Problem& p = *getPPbotProblem(2);
	// Problem& p = *getRingsEqProblem(2);
//	Problem& p = *getRbotProblem();
	//Problem& p = *getRbotIneqProblem();
	Problem& p = *getRPRProblem();
	//MeshBnd bnd(N);
	LipBnd bnd(npoints, p.mBox);
	SimpSort ss(p, bnd);

	BnB bnb(p, ss, eps);
	std::vector<Box> inv, outv, boundv;

	if (nt == 0)
		bnb.solve(inv, outv, boundv);
	else
		bnb.solveOMPAdvanced(inv, outv, boundv, nt);
//    bnb.solveOMPSimple(inv, outv, boundv);
	int cnt = 1;

#if 1
	std::cout << "# inner boxes:\n";
//	printBoxVecGnuplot(cnt, inv, "blue");
    printBoxVecJSON(cnt, inv);
#endif

#if 0
	std::cout << "# bound boxes:\n";
	printBoxVecGnuplot(cnt, boundv, "cyan");
#endif

#if 0
	std::cout << "#outer boxes:\n";
	printBoxVecGnuplot(cnt, outv, "green");
#endif
	//std::cout << "set object 15063 circle at  0,0 size 4 fs empty fc rgb'red'\n";
	//std::cout << "set object 15064 circle at  0,0 size 6 fs empty fc rgb'red'\n";
#if 1
//	std::cout << "set size square\n";
//	std::cout << "set xrange [" << p.mBox.mA[0] << ":" << p.mBox.mB[0] << "]\n";
//	std::cout << "set yrange [" << p.mBox.mA[1] << ":" << p.mBox.mB[1] << "]\n";
//	std::cout << "set key off\n";
//	std::cout << "plot 1/0\n";
//	std::cout << "pause 100\n";
#endif

}
