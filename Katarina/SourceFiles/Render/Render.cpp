#include "Render/Render.h"
namespace Katarina
{
	void Render::outPutColor(std::ostream& out, Vector3 pixel_color, int samplesPerPixel)const
	{
		auto r = pixel_color.x;
		auto g = pixel_color.y;
		auto b = pixel_color.z;

		// Replace NaN components with zero. See explanation in Ray Tracing: The Rest of Your Life.
		if (r != r) r = 0.0;
		if (g != g) g = 0.0;
		if (b != b) b = 0.0;

		// Divide the color by the number of samples and gamma-correct for gamma=2.0.
		real_t scale = 1.0 / samplesPerPixel;
		r = sqrt(scale * r);
		g = sqrt(scale * g);
		b = sqrt(scale * b);

		// Write the translated [0,255] value of each color component.
		out << static_cast<int>(256 * Math::Clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Math::Clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(256 * Math::Clamp(b, 0.0, 0.999)) << '\n';
	}
}