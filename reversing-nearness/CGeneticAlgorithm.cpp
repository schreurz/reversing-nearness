#include "CGeneticAlgorithm.h"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <memory>

using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(unsigned long populationSize, unsigned long numberOfParents, unsigned short n)
{
	std::cout << "Creating GeneticAlgorithm" << std::endl;
	this->populationSize = populationSize;
	this->n = n;
	this->numberOfParents = numberOfParents;

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

shared_ptr<CGrid> CGeneticAlgorithm::go()
{
	// choose parents
	sort(this->population.begin(), this->population.end(), 
		[](shared_ptr<CGrid> l, shared_ptr<CGrid> r) { 
			return (l->getScore() < r->getScore()); 
		});

	// create new population from parents
	vector<shared_ptr<CGrid>> parents(this->population.begin(), this->population.begin() + this->numberOfParents);

	transform(parents.begin(), parents.end() - 1, parents.begin() + 1, this->population.begin(), 
		[](shared_ptr<CGrid> p1, shared_ptr<CGrid> p2) {
			return p1;
		}
	);

	// repeat

	return this->population.front();
}
