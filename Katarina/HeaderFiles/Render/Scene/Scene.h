#pragma once
#include "TypeDefines.h"
namespace Katarina
{
	class CollisionableList;
	class KATARINA_API Scene
	{
	public:
		virtual CollisionableList randomScene() = 0;
	};
}
