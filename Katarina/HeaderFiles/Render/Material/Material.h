#pragma once
#include "core/Math/Vector3.h" 
#include "Render/Ray/Ray.h"
namespace Katarina
{
	class CollideRecord;
	class KATARINA_API Material
	{
	public:
		Material() = default;
		virtual ~Material() = default;
		virtual Vector3 emitted(double u, double v, const Vector3& p) const
		{
			return Vector3(0, 0, 0);
		}
		virtual std::tuple<bool, Vector3, Ray> scatter(const Ray& in, const CollideRecord& rec)const = 0;

	protected:
		Vector3 albedo{};		// ·´ÉäÂÊ
		real_t fuzzy = 0;		// Ä£ºý
	};
}