#pragma once
#include "TypeDefines.h"
#include "Render/Camera/Camera.h"
#include "Render/Scene/Scene.h"

namespace Katarina
{
	class KATARINA_API Render
	{
	public:
		Render() {}
		Render(const Camera& cam, std::shared_ptr<Katarina::Scene> sce) :camera(cam), scene(sce) {}
		virtual void run() const = 0;
		virtual void outPutColor(std::ostream& out, Vector3 pixelColor, int samplesPerPixel)const;
	protected:
		Camera camera;
		std::shared_ptr<Katarina::Scene> scene;
	};
}