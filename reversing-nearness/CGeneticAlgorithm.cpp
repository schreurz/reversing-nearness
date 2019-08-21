#include "CGeneticAlgorithm.h"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <memory>
#include <unordered_set>

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

struct PermutationNode
{
	unsigned short val;
	shared_ptr<PermutationNode> next;
};

vector<shared_ptr<PermutationNode>> permutationGroups(vector<unsigned short> data) {
	vector<shared_ptr<PermutationNode>> permutationNodes;

	for (auto i = 0; i < data.size(); i++) {
		shared_ptr<PermutationNode> p = make_shared<PermutationNode>();
		p->val = data[i];
		permutationNodes.push_back(p);
	}

	for (unsigned short i = 0; i < data.size(); i++) {
		permutationNodes[i]->next = permutationNodes[permutationNodes[i]->val];
	}

	vector<shared_ptr<PermutationNode>> group;
	unordered_set<unsigned short> used;

	for (auto perm : permutationNodes) {
		if (used.insert(perm->val).second) {
			group.push_back(perm);

			shared_ptr<PermutationNode> cur = perm->next;
			while (used.insert(cur->val).second) {
				cur = cur->next;
			}
		}
	}
	
	return group;
}

vector<unsigned short> applyPermutation(const vector<unsigned short>& data, const shared_ptr<PermutationNode>& permutation) {
	vector<unsigned short> mutated(data);
	const unsigned short stop = permutation->val;

	shared_ptr<PermutationNode> cur = permutation;
	while (true) {
		mutated[cur->next->val] = data[cur->val];
		
		cur = cur->next;
		if (cur->val == stop) {
			break;
		}
	}

	return mutated;
}

vector<unsigned short> crossOver(vector<shared_ptr<PermutationNode>> p1, vector<shared_ptr<PermutationNode>> p2, unsigned long size) {
	vector<unsigned short> values(size);
	iota(values.begin(), values.end(), 0);

	for (auto i = 0; i < p1.size() / 2; i++) {
		values = applyPermutation(values, p1[i]);
	}

	for (auto i = 0; i < p2.size() / 2; i++) {
		values = applyPermutation(values, p2[i]);
	}

	return values;
}

const long max_generations = 1000;

shared_ptr<CGrid> CGeneticAlgorithm::go()
{

	for (auto generation = 0; generation < max_generations; generation++) {
		// choose parents
		sort(this->population.begin(), this->population.end(),
			[](shared_ptr<CGrid> l, shared_ptr<CGrid> r) {
				return (l->getScore() < r->getScore());
			});

		// create new population from parents
		const vector<shared_ptr<CGrid>> parents(this->population.begin(), this->population.begin() + this->numberOfParents);

		vector<shared_ptr<CGrid>> nextGeneration(this->populationSize);

		for (auto i = 0; i < this->populationSize; i++) {
			auto parent1 = parents[rand() % parents.size()];
			auto parent2 = parents[rand() % parents.size()];

			vector<shared_ptr<PermutationNode>> group1 = permutationGroups(parent1->gridData());
			vector<shared_ptr<PermutationNode>> group2 = permutationGroups(parent2->gridData());

			unsigned long gridSize = this->n * this->n;
			shared_ptr<CGrid> newOrg = make_shared<CGrid>(crossOver(group1, group2, gridSize), this->n);

			while (rand() % 5 != 0) {
				newOrg = newOrg->swap(rand() % gridSize, rand() % gridSize);
			}

			nextGeneration[i] = newOrg;
		}

		this->population = nextGeneration;
	}

	sort(this->population.begin(), this->population.end(),
		[](shared_ptr<CGrid> l, shared_ptr<CGrid> r) {
			return (l->getScore() < r->getScore());
		});

	return this->population.front();
}
