#ifndef _DATATYPE_H_
#define _DATATYPE_H_

#include "Header.h"

struct Node
{
	size_t ID;
	static const size_t dimension = 3;
	array<double, dimension> coordinates;
	bool isInternal;

	Node() = default;
	Node(size_t, const array<double, dimension>&, bool);

	bool operator<(const Node&) const;

	friend ostream& operator<<(ostream&, const Node&);
	friend ostream& operator<<(ostream&, const vector<Node>&);
	friend ostream& operator<<(ostream&, const array<double, 3>&);
};

struct FiniteElement
{
	size_t finiteID;
	size_t geometryID;
	vector<size_t> nodeID;
	vector<double> centers;

	friend ostream& operator<<(ostream&, const FiniteElement&);
	friend ostream& operator<<(ostream&, const vector<FiniteElement>&);
};

struct Edge
{
	pair<size_t, size_t> edgeNodes;
	int middleNode = -1;

	Edge(size_t, size_t);

	void updateMiddle(size_t);

	Edge& operator=(const Edge&);
	bool operator==(const Edge&) const;

	friend istream& operator>>(istream&, Edge&);
	friend ostream& operator<<(ostream&, const Edge&);
};

#endif // !_DATATYPE_H_