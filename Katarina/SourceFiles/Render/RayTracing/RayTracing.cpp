#include "Render/RayTracing/RayTracing.h"
#include "Core/Log/Log.h"
#include "Render/Material/Material.h"
namespace Katarina
{
	void RayTracing::run() const
	{
		// Image
		const auto aspectRatio = 16.0 / 9.0;
		const int imageWidth = 1200;
		const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
		const int samples_per_pixel = 10;
		// World
		auto world = scene->randomScene();

		// Render
		std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		// 遍历每个图片的像素
		for (int j = imageHeight - 1; j >= 0; --j)
		{
			std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
			for (int i = 0; i < imageWidth; ++i) {
				Vector3 pixel(0, 0, 0);
				for (int s = 0; s < samples_per_pixel; ++s) {
					real_t u = (i + Math::RandomDouble()) / (imageWidth - 1);		// 采样点的x坐标
					real_t v = (j + Math::RandomDouble()) / (imageHeight - 1);		// 采样点的y坐标
					Ray r = camera.getRay(u, v);									// 根据摄像机位置生成射线
					pixel += r.spread(world, maxRayDepth);						// 射线递归遍历场景中碰撞到的物体，直到达到最大递归次数
				}
				outPutColor(std::cout, pixel, samples_per_pixel);
			}
		}
	}
}

