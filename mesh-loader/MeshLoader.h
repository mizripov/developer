#ifndef _MESHLOADER_H_
#define _MESHLOADER_H_

#include "DataType.h"
#include "Hash.h"

class MeshLoader
{
public:
	virtual void loadMesh(const string&) = 0;
	virtual void extratask(const string&) = 0;
	virtual ~MeshLoader() = default;

	const vector<Node>& getNodes();
	const vector<FiniteElement>& getFiniteElement();
	const vector<FiniteElement>& getBoundaryElement();

	vector<size_t> getFiniteElementID(size_t, size_t, size_t);
	vector<size_t> getFiniteElementEdge(size_t, size_t);
	vector<size_t> getNodesIDByBorderID(size_t);
	vector<Node> getNodesByBorderID(size_t);

	vector<size_t> getFiniteElementIDSurface(size_t);
	vector<size_t> getFiniteElementIDVolume(size_t);

	static void printNodes(const vector<Node>&);
	static void printFiniteElements(const vector<FiniteElement>&);

	void insertNodeMiddle();

	vector<set<size_t>> createNeighboursVector();

	double getVolume(const FiniteElement&, const vector<Node>&);
	double getCenter_X(const FiniteElement&, const vector<Node>&);
	double getCenter_Y(const FiniteElement&, const vector<Node>&);
	double getCenter_Z(const FiniteElement&, const vector<Node>&);

protected:
	vector<Node> nodes;
	vector<FiniteElement> finiteElement;
	vector<FiniteElement> boundaryElement;

private:
	Node getMiddleNode(const Edge&);
	array<double, 3> getMiddleEdge(const Edge&);
	array<double, 3> getCoordinate(size_t);
};

#endif // !_MESHLOADER_H_
