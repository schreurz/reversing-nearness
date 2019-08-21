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

//TODO needs fixing, does not work when two permutations are not mutually exclusive.
void applyPermutation(vector<unsigned short>& data, const shared_ptr<PermutationNode>& permutation) {
	unsigned short stop = permutation->val;
	data[stop] = permutation->next->val;
	shared_ptr<PermutationNode> cur = permutation->next;
	while (cur->val != stop) {
		data[cur->val] = cur->next->val;
		cur = cur->next;
	}
}

vector<unsigned short> crossOver(vector<shared_ptr<PermutationNode>> p1, vector<shared_ptr<PermutationNode>> p2, unsigned long size) {
	vector<unsigned short> values(size);
	iota(values.begin(), values.end(), 0);

	for (auto i = 0; i < p1.size() / 2; i++) {
		applyPermutation(values, p1[i]);
	}

	for (auto i = 0; i < p2.size() / 2; i++) {
		applyPermutation(values, p2[i]);
	}

	return values;
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
		[this](shared_ptr<CGrid> p1, shared_ptr<CGrid> p2) {
			// this is where we create the next generation
			vector<unsigned short> p1Data = p1->gridData();
			vector<unsigned short> p2Data = p2->gridData();

			vector<shared_ptr<PermutationNode>> group1 = permutationGroups(p1Data);
			vector<shared_ptr<PermutationNode>> group2 = permutationGroups(p2Data);
			
			unsigned long gridSize = this->n * this->n;
			
			vector<unsigned short> newGen = crossOver(group1, group2, gridSize);

			return make_shared<CGrid>(newGen, this->n);
		}
	);

	// repeat

	return this->population.front();
}
