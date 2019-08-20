#include "CGrid.h"

#include <iostream>

CGrid::CGrid(const unsigned short n)
{
	this->n = n;
	unsigned long elementsLength = n * n;
	this->elements = vector<unsigned short>(elementsLength, 0);
	for (unsigned short i = 0; i < elements.size(); i++) {
		elements[i] = i;
	}
	this->score = evaluate();
}

CGrid::CGrid(vector<unsigned short> values, unsigned short n)
{
	this->n = n;
	this->elements = vector<unsigned short>(values);
	this->score = this->evaluate();
}

CGrid::~CGrid()
{
}

CGrid::CGrid(const CGrid& g2)
{
	this->n = g2.n;
	this->score = g2.score;
	this->elements = g2.elements;
}

unsigned short CGrid::x(unsigned short index) const
{
	return index % this->n;
}

unsigned short CGrid::y(unsigned short index) const
{
	return index / this->n;
}

unsigned short CGrid::index(unsigned short x, unsigned short y) const
{
	return (y * this->n) + x;
}

shared_ptr<CGrid> CGrid::swap(unsigned short i1, unsigned short i2) const
{
	vector<unsigned short> elements = this->elements;

	unsigned short tmp = elements[i1];
	elements[i1] = elements[i2];
	elements[i2] = tmp;

	return make_shared<CGrid>(CGrid(elements, n));
}

unsigned long long CGrid::getScore() const
{
	return this->score;
}

unsigned short CGrid::getN() const
{
	return this->n;
}

unsigned long long CGrid::distanceSq(unsigned short i, unsigned short j, unsigned short n) const
{
	unsigned long long x1, x2, y1, y2;
	x1 = (unsigned long long) this->x(i);
	y1 = (unsigned long long) this->y(i);
	x2 = (unsigned long long) this->x(j);
	y2 = (unsigned long long) this->y(j);

	unsigned long long dx = x1 > x2 ? x1 - x2 : x2 - x1;
	unsigned long long dy = y1 > y2 ? y1 - y2 : y2 - y1;

	if (dx * 2 > this->n) {
		dx = n - dx;
	}

	if (dy * 2 > this->n) {
		dy = n - dy;
	}

	return (dx * dx) + (dy * dy);
}

unsigned long long CGrid::evaluate() const
{
	unsigned long long score = 0;

	for (unsigned short i = 0; i < this->elements.size(); i++) {
		for (unsigned short j = i + 1; j < this->elements.size(); j++) {
			unsigned long long dist1 = distanceSq(i, j, this->n);
			unsigned long long dist2 = distanceSq(this->elements[i], this->elements[j], this->n);
			score += dist1 * dist2;
		}
	}

	return score;
}

char getChar(unsigned short val) {
	return (char)(val < 26 ? 'A' + val : '1' + val - 26);
}

ostream& operator<<(ostream& out, const CGrid& grid)
{
	unsigned short val;
	for (unsigned short y = 0; y < grid.n; y++) {
		out << "(";
		for (unsigned short x = 0; x < grid.n - 1; x++) {
			val = grid.elements[grid.index(x, y)];
			out << getChar(grid.x(val)) << getChar(grid.y(val)) << ", ";
		}
		if (y < grid.n - 1) {
			val = grid.elements[grid.index(grid.n - 1, y)];
			out << getChar(grid.x(val)) << getChar(grid.y(val)) << "),\n";
		}
	}
	val = grid.elements.back();
	out << getChar(grid.x(val)) << getChar(grid.y(val)) << ")";

	return out;
}
