#pragma once
#include <tuple>
#include "Render/Collide/CollideRecord.h"
namespace Katarina
{
	class Ray;
	class KATARINA_API Collisionable
	{
	public:
		Collisionable() = default;
		virtual ~Collisionable() {}
		// tMin和tMax用于限制射线长度
		virtual std::pair<bool, CollideRecord> collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const = 0;
	};
}

