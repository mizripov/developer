#include "AneuMeshLoader.h"

void AneuMeshLoader::loadMesh(const string& path)
{
	ifstream file(path);
	if (!file.is_open())
	{
		throw FileNotFound();
	}

	size_t counter, dimension;
	file >> counter >> dimension;
	nodes.reserve(counter);
	for (size_t i = 0; i < counter; ++i)
	{
		Node temp = Node();
		file >> temp.coordinates[0] >> temp.coordinates[1] >> temp.coordinates[2];
		temp.ID = i;
		temp.isInternal = false;
		nodes.push_back(temp);
	}

	file >> counter >> dimension;
	finiteElement.reserve(counter);
	for (size_t i = 0; i < counter; ++i)
	{
		FiniteElement temp;
		size_t nodeID;
		file >> temp.geometryID;
		for (size_t j = 0; j < dimension; ++j)
		{
			file >> nodeID;
			temp.nodeID.push_back(nodeID);
		}

		temp.centers.push_back(getCenter_X(temp, nodes));
		temp.centers.push_back(getCenter_Y(temp, nodes));
		temp.centers.push_back(getCenter_Z(temp, nodes));

		temp.finiteID = i;
		finiteElement.push_back(move(temp));
	}

	file >> counter >> dimension;
	boundaryElement.reserve(counter);
	for (size_t i = 0; i < counter; ++i)
	{
		FiniteElement temp;
		size_t nodeID;
		file >> temp.geometryID;
		for (size_t j = 0; j < dimension; ++j)
		{
			file >> nodeID;
			temp.nodeID.push_back(nodeID);
		}

		temp.finiteID = i;
		boundaryElement.push_back(move(temp));
	}

	file.close();
}

void AneuMeshLoader::extratask(const string& path)
{
	ofstream file(path);
	if (!file.is_open())
	{
		throw FileNotFound();
	}
	vector<FiniteElement> container = this->getFiniteElement();
	vector<Node> nodes = this->getNodes();

	ranges::sort(container, [&](const FiniteElement& first, const FiniteElement& second)
		{
			return getVolume(first, nodes) > getVolume(second, nodes);
		});

	ranges::copy(container | views::drop(10) | views::take(11), ostream_iterator<FiniteElement>(file));
}