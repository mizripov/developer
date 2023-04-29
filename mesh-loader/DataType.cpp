#include "DataType.h"

// NODE

Node::Node(size_t id, const array<double, dimension>& coordinates, bool isInternal)
: ID(id), coordinates(coordinates), isInternal(isInternal)
{

}

bool Node::operator<(const Node& node) const
{
	return ID < node.ID;
}

ostream& operator<<(ostream& out, const Node& node)
{
	out << setw(3) << node.ID << " "
		<< setw(10) << node.coordinates[0] << " "
		<< setw(10) << node.coordinates[1] << " "
		<< setw(10) << node.coordinates[2] << " "
		<< node.isInternal << endl;
	return out;
}

ostream& operator<<(ostream& out, const vector<Node>& nodes)
{
	for (const auto& node : nodes)
	{
		out << node;
	}
	return out;
}

ostream& operator<<(ostream& out, const array<double, 3>& arr)
{
	for (const auto& coordinates : arr)
	{
		out << coordinates;
	}
	return out;
}


//FINITEELEMENT

ostream& operator<<(ostream& out, const FiniteElement& finEl)
{
	out << finEl.finiteID << " " << setw(4) << finEl.geometryID << " ";
	for (const auto& node : finEl.nodeID)
	{
		out << setw(4) << node << " ";
	}
	out << fixed
		<< setw(6) << '\t' << finEl.centers[0]
		<< setw(6) << '\t' << finEl.centers[1]
		<< setw(6) << '\t' << finEl.centers[2]
		<< endl;
	return out;
}

ostream& operator<<(ostream& out, const vector<FiniteElement>& finEls)
{
	for (const auto& finEl : finEls)
	{
		out << finEl;
	}
	return out;
}


//EDGE

Edge::Edge(size_t firstNodeID, size_t secondNodeID) : edgeNodes({ firstNodeID, secondNodeID })
{

}

void Edge::updateMiddle(size_t midNode)
{
	middleNode = midNode;
}

Edge& Edge::operator=(const Edge& edge)
{
	if (this != &edge)
	{
		this->edgeNodes = edge.edgeNodes;
		this->middleNode = edge.middleNode;
	}
	return *this;
}

bool Edge::operator==(const Edge& edge) const
{
	return (this->edgeNodes.first == edge.edgeNodes.first) && (this->edgeNodes.second == edge.edgeNodes.second);
}

istream& operator>>(istream& in, Edge& edge)
{
	in >> edge.edgeNodes.first >> edge.edgeNodes.second;
	return in;
}

ostream& operator<<(ostream& out, const Edge& edge)
{
	out << edge.edgeNodes.first << ", " << edge.edgeNodes.second << endl;
	return out;
}