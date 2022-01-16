#pragma once
#include <vector>
#include"Core/Math/Vector3.h"
#include"TypeDefines.h"
namespace Katarina
{
	class KATARINA_API Model
	{
	private:
		std::vector<Vector3> verts_;
		std::vector<std::vector<int> > faces_;
	public:
		Model(const char* filename);
		~Model();
		int nverts();
		int nfaces();
		Vector3 vert(int i);
		std::vector<int> face(int idx);
	};

}