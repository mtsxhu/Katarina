#include "Core/Application/Application.h"
#include "Scene/Scene.h"
#include "Core/Math/Vector3.h"
#include "Render/Camera/Camera.h"
#include "Render/Collide/CollideRecord.h"
#include "Render/Collide/Collisionable.h"
#include "Render/Collide/CollisionableList.h"
namespace Katarina
{
	Vector3 ray_Vector3(const Ray& r, const Collisionable& world, int depth) {
		// If we've exceeded the ray bounce limit, no more light is gathered.
		if (depth <= 0)
			return Vector3(0, 0, 0);
		auto [ok, rec] = world.collision(r, 0.001, infinity);
		if (ok) {

			auto [ok, attenuation, scattered] = rec.material->scatter(r, rec);
			if (ok)
				return attenuation * ray_Vector3(scattered, world, depth - 1);
			return Vector3(0, 0, 0);
		}

		Vector3 unit_direction = r.getDirection().normalize();
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
	}

	void write_color(std::ostream& out, Vector3 pixel_color, int samples_per_pixel) {
		auto r = pixel_color.x;
		auto g = pixel_color.y;
		auto b = pixel_color.z;

		// Replace NaN components with zero. See explanation in Ray Tracing: The Rest of Your Life.
		if (r != r) r = 0.0;
		if (g != g) g = 0.0;
		if (b != b) b = 0.0;

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		auto scale = 1.0 / samples_per_pixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(256 * Math::Clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Math::Clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Math::Clamp(b, 0.0, 0.999)) << '\n';
	}

	void Application::Run()
	{
		// Image

		const auto aspect_ratio = 3.0 / 2.0;
		const int image_width = 1200;
		const int image_height = static_cast<int>(image_width / aspect_ratio);
		const int samples_per_pixel = 500;
		const int max_depth = 50;

		// World

		auto world = randomScene();

		// Camera

		Vector3 lookfrom(13, 2, 3);
		Vector3 lookat(0, 0, 0);
		Vector3 vup(0, 1, 0);
		auto dist_to_focus = 10.0;
		auto aperture = 0.1;

		Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

		// Render

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = image_height - 1; j >= 0; --j)
		{
			std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
			for (int i = 0; i < image_width; ++i) {
				Vector3 pixel_Vector3(0, 0, 0);
				for (int s = 0; s < samples_per_pixel; ++s) {
					auto u = (i + Math::RandomDouble()) / (image_width - 1);
					auto v = (j + Math::RandomDouble()) / (image_height - 1);
					Ray r = cam.getRay(u, v);
					pixel_Vector3 += ray_Vector3(r, world, max_depth);
				}
				write_color(std::cout, pixel_Vector3, samples_per_pixel);
			}
		}
	}
}
