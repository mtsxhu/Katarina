#pragma once
#include "Render/Material/Material.h"
#include "Render/Material/Reflaction/Lambertian.h"
#include "Render/Material/Reflaction/Metal.h"
#include "Render/Material/Reflaction/Dielectric.h"
#include "Render/Geometry/Sphere.h"
#include "Core/Math/Vector3.h"
#include "Render/Collide/CollisionableList.h"
#include <memory>
namespace Katarina
{
	CollisionableList randomScene()
	{
		CollisionableList world;

		auto ground_Material = std::make_shared<Lambertian>(Vector3(0.5, 0.5, 0.5));
		world.add(std::make_shared<Sphere>(Vector3(0, -1000, 0), 1000, ground_Material));

		for (int a = -11; a < 11; a++) {
			for (int b = -11; b < 11; b++) {
				auto choose_mat = Math::RandomDouble();
				Vector3 center(a + 0.9 * Math::RandomDouble(), 0.2, b + 0.9 * Math::RandomDouble());

				if ((center - Vector3(4, 0.2, 0)).length() > 0.9) {
					std::shared_ptr<Material> Sphere_Material;

					if (choose_mat < 0.8) {
						// diffuse
						auto albedo = Math::Random() * Math::Random();
						Sphere_Material = std::make_shared<Lambertian>(albedo);
						world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
					}
					else if (choose_mat < 0.95) {
						// metal
						auto albedo = Math::Random(0.5, 1);
						auto fuzz = Math::RandomDouble(0, 0.5);
						Sphere_Material = std::make_shared<Metal>(albedo, fuzz);
						world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
					}
					else {
						// glass
						Sphere_Material = std::make_shared<Dielectric>(1.5);
						world.add(std::make_shared<Sphere>(center, 0.2, Sphere_Material));
					}
				}
			}
		}

		auto Material1 = std::make_shared<Dielectric>(1.5);
		world.add(std::make_shared<Sphere>(Vector3(0, 1, 0), 1.0, Material1));

		auto Material2 = std::make_shared<Lambertian>(Vector3(0.4, 0.2, 0.1));
		world.add(std::make_shared<Sphere>(Vector3(-4, 1, 0), 1.0, Material2));

		auto Material3 = std::make_shared<Metal>(Vector3(0.7, 0.6, 0.5), 0.0);
		world.add(std::make_shared<Sphere>(Vector3(4, 1, 0), 1.0, Material3));

		return world;
	}
}
