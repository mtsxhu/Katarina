#include "Render/Material/Reflaction/Lambertian.h"
#include "Render/Collide/CollideRecord.h"
namespace Katarina
{
	std::tuple<bool, Vector3, Ray> Lambertian::scatter(const Ray& in, const CollideRecord& rec) const
	{
		auto scatter_direction = rec.normal + Math::RandomUnitVector();

		if (Math::nearZero(scatter_direction))
		{
			scatter_direction = rec.normal;
		}
		auto scattered = Ray(rec.position, scatter_direction);
		auto attenuation = albedo;
		return std::make_tuple(true, attenuation, scattered);
	}
}