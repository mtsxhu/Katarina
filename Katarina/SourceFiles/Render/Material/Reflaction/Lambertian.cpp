#include "Render/Material/Reflaction/Lambertian.h"
#include "Render/Collide/CollideRecord.h"
namespace Katarina
{
	std::tuple<bool, Vector3, Ray> Lambertian::scatter(const Ray& in, const CollideRecord& rec) const
	{
		Vector3 scatter_direction = rec.normal + Math::RandomUnitVector();			// 随机向一个方向进行反射

		if (scatter_direction.nearZearo())
		{
			scatter_direction = rec.normal;
		}
		auto scattered = Ray(rec.position, scatter_direction);
		auto attenuation = albedo;
		return std::make_tuple(true, attenuation, scattered);
	}
}