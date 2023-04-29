#include "MeshLoader.h"

const vector<Node>& MeshLoader::getNodes()
{
	return nodes;
}

const vector<FiniteElement>& MeshLoader::getFiniteElement()
{
	return finiteElement;
}

const vector<FiniteElement>& MeshLoader::getBoundaryElement()
{
	return boundaryElement;
}

vector<size_t> MeshLoader::getFiniteElementID(size_t id_1, size_t id_2, size_t id_3)
{
	vector<size_t> result;
	auto check = [id_1, id_2, id_3, &result](const FiniteElement& elem) 
	{
		if ((any_of(elem.nodeID.begin(), elem.nodeID.end(), [id_1](const size_t id) { return id == id_1; })) &&
			(any_of(elem.nodeID.begin(), elem.nodeID.end(), [id_2](const size_t id) { return id == id_2; })) &&
			(any_of(elem.nodeID.begin(), elem.nodeID.end(), [id_3](const size_t id) { return id == id_3; }))) 
		{
			result.push_back(elem.finiteID);
		}
	};
	for_each(finiteElement.begin(), finiteElement.end(), check);
	return result;
}

vector<size_t> MeshLoader::getFiniteElementEdge(size_t id_1, size_t id_2)
{
	vector<size_t> result;
	auto check = [id_1, id_2, &result](const FiniteElement& elem) 
	{
		if ((any_of(elem.nodeID.begin(), elem.nodeID.end(), [id_1](const size_t id) { return id == id_1; })) &&
			(any_of(elem.nodeID.begin(), elem.nodeID.end(), [id_2](const size_t id) { return id == id_2; })))
		{
			result.push_back(elem.finiteID);
		}
	};
	for_each(finiteElement.begin(), finiteElement.end(), check);
	return result;
}

vector<size_t> MeshLoader::getNodesIDByBorderID(size_t id)
{
	set<size_t> result;
	for (auto current = boundaryElement.begin(); current != boundaryElement.end(); ) 
	{
		current = find_if(current, boundaryElement.end(), [id](const FiniteElement& elem) 
			{
				return elem.geometryID == id;
			});

		if (current != boundaryElement.end())
		{
			for (const auto& node : current->nodeID) 
			{
				const Node &nodeID = nodes[node - 1];
				result.insert(nodeID.ID);
			}
			++current;
		}
	}
	return vector<size_t>(result.begin(), result.end());
}

vector<Node> MeshLoader::getNodesByBorderID(size_t id)
{
	set<Node> result;
	for (auto current = boundaryElement.begin(); current != boundaryElement.end(); ) 
	{
		current = find_if(current, boundaryElement.end(), [id](const FiniteElement& elem) 
			{
				return elem.geometryID == id;
			});

		if (current != boundaryElement.end()) 
		{
			for (const auto& node : current->nodeID) 
			{
				Node nodeID = nodes[node - 1];
				result.insert(nodeID);
			}
			++current;
		}
	}
	return vector<Node>(result.begin(), result.end());
}

vector<size_t> MeshLoader::getFiniteElementIDSurface(size_t id)
{
	vector<size_t> result;
	auto check = [id, &result](const FiniteElement& elem)
	{
		if (elem.geometryID == id)
		{
			result.push_back(elem.finiteID);
		}
	};
	for_each(finiteElement.begin(), finiteElement.end(), check);
	return result;
}

vector<size_t> MeshLoader::getFiniteElementIDVolume(size_t id)
{
	vector<size_t> result;
	auto check = [id, &result](const FiniteElement& elem)
	{
		if (elem.geometryID == id)
		{
			result.push_back(elem.finiteID);
		}
	};
	for_each(boundaryElement.begin(), boundaryElement.end(), check);
	return result;
}

void MeshLoader::printNodes(const vector<Node>& nodes)
{
	cout << nodes;
}

void MeshLoader::printFiniteElements(const vector<FiniteElement>& elem)
{
	cout << elem;
}

void MeshLoader::insertNodeMiddle()
{
	unordered_set<Edge, Hash> edge;
	for (auto& elem : finiteElement)
	{
		vector<size_t> elemNodeID = elem.nodeID;
		for (size_t first = 0; first < 4; ++first) 
		{
			for (size_t second = first + 1; second < 4; ++second) 
			{
				Edge currentEdge(elemNodeID[first], elemNodeID[second]);
				if (edge.insert(currentEdge).second)
				{
					Node newNode = getMiddleNode(currentEdge);
					currentEdge.updateMiddle(newNode.ID);
					nodes.push_back(newNode);
					elem.nodeID.push_back(newNode.ID);
				}
				else 
				{
					elem.nodeID.push_back(currentEdge.middleNode);
				}
			}
		}
	}
	for (auto& boundElem : boundaryElement)
	{
		vector<size_t> boundElemNodeID = boundElem.nodeID;
		for (size_t first = 0; first < 3; ++first) 
		{
			for (size_t second = first + 1; second < 3; ++second) 
			{
				auto currentEdgeIter = edge.find({ boundElemNodeID[first], boundElemNodeID[second] });
				if (currentEdgeIter == edge.end()) 
				{
					currentEdgeIter = edge.find({ boundElemNodeID[second], boundElemNodeID[first] });
				}
				boundElemNodeID.push_back(currentEdgeIter->middleNode);
			}
		}
	}
}

vector<set<size_t>> MeshLoader::createNeighboursVector()
{
	vector<set<size_t>> neighbours;
	neighbours.reserve(nodes.size() + 1);
	for (const auto& elem : boundaryElement)
	{
		for (const auto& nodeID : elem.nodeID)
		{
			for (const auto& anotherNodeID : elem.nodeID)
			{
				if (nodeID != anotherNodeID)
				{
					neighbours[nodeID].insert(anotherNodeID);
				}
			}
		}
	}
	return neighbours;
}

//Вычисляет объем
double MeshLoader::getVolume(const FiniteElement& elem, const vector<Node>& nodes)
{
	return 1 / 6 * (nodes[elem.nodeID[1] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0] * nodes[elem.nodeID[2] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] * nodes[elem.nodeID[3] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] -
					nodes[elem.nodeID[1] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0] * nodes[elem.nodeID[2] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] * nodes[elem.nodeID[3] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] -
					nodes[elem.nodeID[1] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] * nodes[elem.nodeID[2] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0] * nodes[elem.nodeID[3] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] +
					nodes[elem.nodeID[1] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] * nodes[elem.nodeID[2] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] * nodes[elem.nodeID[3] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0] +
					nodes[elem.nodeID[1] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] * nodes[elem.nodeID[2] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0] * nodes[elem.nodeID[3] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] -
					nodes[elem.nodeID[1] - 1].coordinates[2] - nodes[elem.nodeID[0] - 1].coordinates[2] * nodes[elem.nodeID[2] - 1].coordinates[1] - nodes[elem.nodeID[0] - 1].coordinates[1] * nodes[elem.nodeID[3] - 1].coordinates[0] - nodes[elem.nodeID[0] - 1].coordinates[0]);
}

//Возвращает первую координату центра
double MeshLoader::getCenter_X(const FiniteElement& elem, const vector<Node>& nodes)
{
	return (nodes[elem.nodeID[0] - 1].coordinates[0] + nodes[elem.nodeID[1] - 1].coordinates[0] + nodes[elem.nodeID[2] - 1].coordinates[0] + nodes[elem.nodeID[3] - 1].coordinates[0]) / 4;
}

//Возвращает вторую координату центра
double MeshLoader::getCenter_Y(const FiniteElement& elem, const vector<Node>& nodes)
{
	return (nodes[elem.nodeID[0] - 1].coordinates[1] + nodes[elem.nodeID[1] - 1].coordinates[1] + nodes[elem.nodeID[2] - 1].coordinates[1] + nodes[elem.nodeID[3] - 1].coordinates[1]) / 4;
}

//Возвращает третью координату центра
double MeshLoader::getCenter_Z(const FiniteElement& elem, const vector<Node>& nodes)
{
	return (nodes[elem.nodeID[0] - 1].coordinates[2] + nodes[elem.nodeID[1] - 1].coordinates[2] + nodes[elem.nodeID[2] - 1].coordinates[2] + nodes[elem.nodeID[3] - 1].coordinates[2]) / 4;
}

Node MeshLoader::getMiddleNode(const Edge& edge)
{
	Node result(nodes.size() + 1, getMiddleEdge(edge), false);
	return result;
}

array<double, 3> MeshLoader::getMiddleEdge(const Edge& edge)
{
	double middleX = ((nodes.at(edge.edgeNodes.first - 1).coordinates.at(0))
		+ (nodes.at(edge.edgeNodes.second - 1).coordinates.at(0))) / 2;
	double middleY = ((nodes.at(edge.edgeNodes.first - 1).coordinates.at(1))
		+ (nodes.at(edge.edgeNodes.second - 1).coordinates.at(1))) / 2;
	double middleZ = ((nodes.at(edge.edgeNodes.first - 1).coordinates.at(2))
		+ (nodes.at(edge.edgeNodes.second - 1).coordinates.at(2))) / 2;
	return { middleX, middleY, middleZ };
}

array<double, 3> MeshLoader::getCoordinate(size_t id)
{
	return nodes.at(id).coordinates;
}