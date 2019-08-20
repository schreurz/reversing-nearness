#pragma once

#include <vector>
#include <memory>

#include "CGrid.h"

using namespace std;

class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(unsigned long populationSize, unsigned short n);
	~CGeneticAlgorithm();

	unsigned long long go();

private:
	unsigned long populationSize;
	vector<shared_ptr<CGrid>> population;
	unsigned short n;
};
