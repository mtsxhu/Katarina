#pragma once
#include "TypeDefines.h"
#include "Core/Math/Vector3.h"
#include "Render/Material/Material.h"
#include "Render/Ray/Ray.h"
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
		_FORCE_INLINE_ void setFaceNormal(const Ray& r, const Vector3& outwardNormal)
		{
			frontFace = Vector3::dot(r.getDirection(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};
}