#pragma once
#include "Core/Math/Vector3.h"
#include<vector>
namespace Katarina
{
	class KATARINA_API Ray
	{
	private:
		Vector3 origin;
		Vector3 direction;

	public:
		Ray() = default;
		~Ray() = default;
		Ray(const Vector3& org, const Vector3& dir)
			:origin(org), direction(dir) {
			direction.normalize();
		}

		Vector3 getOrigin() const { return origin; }
		Vector3 getDirection() const { return direction; }

		Vector3 pointAt(const real_t& t)const { return origin + direction * t; }
	};

}


