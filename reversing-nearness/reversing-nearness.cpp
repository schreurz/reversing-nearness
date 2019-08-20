// reversing-nearness.cpp : Defines the entry point for the application.
//

#include "reversing-nearness.h"

#include <memory>

#include "CGeneticAlgorithm.h"
#include "CGrid.h"

using namespace std;

static const unsigned short N = 6;

int main()
{
	cout << "Hello CMake." << endl;
	CGeneticAlgorithm genAlg(10, N);

	unsigned long long score = genAlg.go();

	cout << "Best score: " << score << endl;

	return 0;
}
