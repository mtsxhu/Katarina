#pragma once

#include "Core/Math/Vector3.h"
#include "TypeDefines.h"
#include "Render/Collide/Collisionable.h"
#include <tuple>
namespace Katarina
{
	class KATARINA_API Dielectric :public Material
	{
	public:
		Dielectric(real_t RefractionIndex) : RefractionIndex(RefractionIndex) {}
		virtual std::tuple<bool, Vector3, Ray> scatter(const Ray& in, const CollideRecord& rec)const override
		{
			auto attenuation = Vector3(1.0, 1.0, 1.0);
			real_t refractionRatio = rec.frontFace ? (1.0 / this->RefractionIndex) : this->RefractionIndex;
			Vector3 unitDirection = in.getDirection().normalize();

			real_t cosTheta = fmin(Vector3::dot(-unitDirection, rec.normal), 1.0);
			double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
			bool cannotRefract = refractionRatio * sinTheta > 1.0;

			Vector3 refracted;
			if (cannotRefract || reflectance(cosTheta, refractionRatio) > Math::RandomDouble())
			{
				refracted = unitDirection.reflect(rec.normal);
			}
			else
			{
				refracted = unitDirection.refract(rec.normal, refractionRatio);
			}

			Ray scattered = Ray(rec.position, refracted);
			return std::make_tuple(true, refracted, scattered);
		}

	private:
		static real_t reflectance(real_t cosine, real_t refIdx)
		{
			// Schlick Approximation,菲涅尔方程的近似
			auto r0 = (1 - refIdx) / (1 + refIdx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}
	private:
		real_t RefractionIndex;
	};

}