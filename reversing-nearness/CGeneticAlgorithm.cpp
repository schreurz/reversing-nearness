#include "CGeneticAlgorithm.h"

#include <iostream>

using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(unsigned long populationSize, unsigned short n)
{
	std::cout << "Creating GeneticAlgorithm" << std::endl;
	this->populationSize = populationSize;
	this->n = n;
	for (unsigned long i = 0; i < populationSize; i++) {
		this->population.push_back(make_shared<CGrid>(n));
	}
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

unsigned long long CGeneticAlgorithm::go()
{
	this->population[0] = this->population[0]->swap(0, 1);
	return this->population[0]->getScore();
}
