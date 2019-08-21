#pragma once

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class CGrid
{
public:
	CGrid(unsigned short n);
	CGrid(vector<unsigned short> values, unsigned short n);
	virtual ~CGrid();
	CGrid(const CGrid& p2);
	
	unsigned short x(unsigned short index) const;
	unsigned short y(unsigned short index) const;
	unsigned short index(unsigned short x, unsigned short y) const;
	shared_ptr<CGrid> swap(unsigned short i1, unsigned short i2) const;

	unsigned long long getScore() const;
	unsigned short getN() const;
	vector<unsigned short> gridData() const;

	friend ostream& operator << (ostream& out, const CGrid& grid);

private:
	unsigned long long distanceSq(unsigned short i, unsigned short j, unsigned short n) const;
	unsigned long long evaluate() const;

	unsigned short n;
	vector<unsigned short> elements;
	unsigned long long score;
};
