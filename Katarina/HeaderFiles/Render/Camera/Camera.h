#pragma once
#include"Core/Math/Vector3.h"
#include"Render/Ray/Ray.h"
#include "Scene/Scene.h"
#include <vector>
#include "Core/Math/Vector3.h"
#include "Core/Math/Math.h"
namespace Katarina
{
	class KATARINA_API Camera
	{
	public:
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, real_t vfov, real_t aspect_ratio, real_t aperture, real_t focus_dist) {
			auto theta = Math::Degrees2Radians(vfov);
			auto h = tan(theta / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;

			w = Vector3(lookfrom - lookat).normalize();
			u = Vector3::cross(vup, w).normalize();
			v = Vector3::cross(w, u);

			origin = lookfrom;
			horizontal = focus_dist * viewport_width * u;
			vertical = focus_dist * viewport_height * v;
			lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

			lensRadius = aperture / 2;
		}

		Ray getRay(real_t u, real_t v) const
		{
			return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
		}

	private:
		Vector3 origin;
		Vector3 lowerLeftCorner;
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 u, v, w;
		real_t lensRadius;
	};

}
