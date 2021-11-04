#pragma once
#include "Render/Material/Material.h"
#include"Core/Math/Vector3.h"
#include"Core/Math/Math.h"
#include "Render/Ray/Ray.h"
namespace Katarina
{
	class KATARINA_API Lambertian : public Material
	{
	public:
		Lambertian(const Vector3& albedo)
		{
			this->albedo = albedo;
		}
		virtual ~Lambertian() = default;

		virtual std::tuple<bool, Vector3, Ray> scatter(const Ray& in, const CollideRecord& rec) const;
	};
}

