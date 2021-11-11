#pragma once
#include "Render/Render.h"
#include "Render/Scene/RayTracingScene.h"
namespace Katarina
{
	class KATARINA_API RayTracing : public Render
	{
	public:
		RayTracing() = delete;
		RayTracing(const Camera& cam, std::shared_ptr<Katarina::Scene> sce, int depth = 50) :Render(cam, sce), maxRayDepth(depth) {}
		// Í¨¹ý Render ¼Ì³Ð
		virtual void run() const override;
	private:
		int maxRayDepth;
	};
}