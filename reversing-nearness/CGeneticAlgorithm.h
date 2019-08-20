#pragma once

#include <vector>
#include <memory>

#include "CGrid.h"

using namespace std;

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(unsigned long populationSize, unsigned long numberOfParents, unsigned short n);
	~CGeneticAlgorithm();

	shared_ptr<CGrid> go();

private:
	unsigned long populationSize;
	unsigned long numberOfParents;
	vector<shared_ptr<CGrid>> population;
	unsigned short n;
};
