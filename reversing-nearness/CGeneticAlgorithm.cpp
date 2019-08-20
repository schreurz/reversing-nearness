#include "CGeneticAlgorithm.h"

#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(unsigned long populationSize, unsigned short n)
{
	std::cout << "Creating GeneticAlgorithm" << std::endl;
	this->populationSize = populationSize;
	this->n = n;

	unsigned long gridSize = n * n;
	for (unsigned long i = 0; i < populationSize; i++) {
		vector<unsigned short> values(gridSize);
		iota(values.begin(), values.end(), 0);
		random_shuffle(values.begin(), values.end());
		this->population.push_back(make_shared<CGrid>(values, n));
	}
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

unsigned long long CGeneticAlgorithm::go()
{
	return 0;
}
