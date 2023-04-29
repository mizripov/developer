#include "AneuMeshLoader.h"

/*
* реализовать на основе std::ranges
* создать контейнер тетраэдров
* отсортировать по объему
* за один pipeline вывести в файл координаты центров тетраэдров с 10 по 20
*/

int main()
{
    MeshLoader* mesh = new AneuMeshLoader;
    try
    {
        mesh->loadMesh("MeshExample.aneu");
        mesh->extratask("Output.txt");
    }
    catch (FileNotFound& error)
    {
        error.getError();
        delete mesh;
        return 0;
    }

    mesh->printNodes(mesh->getNodes());
    mesh->printFiniteElements(mesh->getFiniteElement());
    //mesh->printFiniteElements(mesh->getBoundaryElement());

    cout << "Finite elements by nodes" << endl;

    auto finElem = mesh->getFiniteElementID(18, 56, 40);
    for (auto elem : finElem)
    {
        cout << elem << " ";
    }
    cout << endl;

    delete mesh;

	return 0;
}
