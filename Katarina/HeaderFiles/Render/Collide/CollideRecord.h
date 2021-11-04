#pragma once
#include "TypeDefines.h"
#include "Core/Math/Vector3.h"
#include "Render/Material/Material.h"
#include <memory>
namespace Katarina
{
	struct KATARINA_API CollideRecord
	{
		real_t t;			// 射线方程的t
		Vector3 position;	// 碰撞交点的位置
		Vector3 normal;		// 碰撞交点的法线
		std::shared_ptr<Material> material; // 碰撞交点的材质
		bool frontFace;
		real_t u;
		real_t v;
	};
}