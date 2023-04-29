#ifndef _ANEUMESHLOADER_H_
#define _ANEUMESHLOADER_H_

#include "MeshLoader.h"
#include "Exception.h"

class AneuMeshLoader : public MeshLoader
{
public:
	void loadMesh(const string&) override;
	void extratask(const string&) override;
};

#endif // !_ANEUMESHLOADER_H_
