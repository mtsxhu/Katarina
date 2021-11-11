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

		// ����ÿ��ͼƬ������
		for (int j = imageHeight - 1; j >= 0; --j)
		{
			std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
			for (int i = 0; i < imageWidth; ++i) {
				Vector3 pixel(0, 0, 0);
				for (int s = 0; s < samples_per_pixel; ++s) {
					real_t u = (i + Math::RandomDouble()) / (imageWidth - 1);		// �������x����
					real_t v = (j + Math::RandomDouble()) / (imageHeight - 1);		// �������y����
					Ray r = camera.getRay(u, v);									// ���������λ����������
					pixel += r.spread(world, maxRayDepth);						// ���ߵݹ������������ײ�������壬ֱ���ﵽ���ݹ����
				}
				outPutColor(std::cout, pixel, samples_per_pixel);
			}
		}
	}
}

