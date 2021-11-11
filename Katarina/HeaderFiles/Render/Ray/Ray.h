#pragma once
#include "Core/Math/Vector3.h"
#include<vector>
namespace Katarina
{
	class Collisionable;
	class KATARINA_API Ray
	{
	private:
		Vector3 origin{};
		Vector3 direction{};
		real_t time = 0;
	public:
		Ray() = default;
		~Ray() = default;
		Ray(const Vector3& org, const Vector3& dir, real_t t = 0) :origin(org), direction(dir), time(t) {}

		Vector3 getOrigin() const { return origin; }
		Vector3 getDirection() const { return direction; }

		Vector3 pointAt(const real_t& t)const { return origin + direction * t; }

		Vector3 spread(const Collisionable& world, int depth)const;
	};

}


