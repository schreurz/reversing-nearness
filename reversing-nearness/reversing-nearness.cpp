// reversing-nearness.cpp : Defines the entry point for the application.
//

#include "reversing-nearness.h"

#include <memory>

#include "CGeneticAlgorithm.h"
#include "CGrid.h"

using namespace std;

static const unsigned short N = 6;

static const unsigned long POPULATION_SIZE = 10000;
static const unsigned long NUMBER_OF_PARENTS = 100;

int main()
{
	cout << "Hello CMake." << endl;
	CGeneticAlgorithm genAlg(POPULATION_SIZE, NUMBER_OF_PARENTS, N);

	unsigned long long score = genAlg.go();

	cout << "Best score: " << score << endl;

	return 0;
}
