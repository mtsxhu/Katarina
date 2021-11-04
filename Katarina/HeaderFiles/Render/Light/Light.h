#pragma once

#include"Core/Math/Vector3.h"
namespace Katarina
{
	class KATARINA_API Light
	{
	public:
		Light(const Vector3& p, const Vector3& i)
			: position(p)
			, intensity(i)
		{}
		virtual ~Light() = default;
		Vector3 position;
		Vector3 intensity;
	};
}
