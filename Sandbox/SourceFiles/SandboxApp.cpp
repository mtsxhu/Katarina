#include "Katarina.h"
#include <memory>
class Sandbox :public Katarina::Application
{
public:
	Sandbox(std::shared_ptr<Katarina::Render> r) :Application(r) {}
	virtual ~Sandbox() {}
};

//Katarina::Application* Katarina::CreateApplication()
//{
//	std::shared_ptr<Katarina::Scene> scene(new Katarina::RayTracingScene);
//	// Camera
//	Vector3 lookfrom(13, 2, 3);	// 摄像机源点
//	Vector3 lookat(0, 0, 0);	// 摄像机目标
//	Vector3 vup(0, 1, 0);		// 向上向量
//	// 光圈和视距用于实现运动模糊
//	auto dist_to_focus = 10.0;	// 视距			
//	auto aperture = 0.1;	// 光圈
//	const auto aspectRatio = 16.0 / 9.0;
//	Camera camera(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);
//
//	std::shared_ptr<Katarina::Render> render(new RayTracing(camera, scene, 50));
//	return new Sandbox(render);
//}


Katarina::Application* Katarina::CreateApplication()
{
	std::shared_ptr<Katarina::Model> model(new Model("C:/Users/LCX/Desktop/Katarina/Sandbox/obj/african_head/african_head.obj"));
	std::shared_ptr<Katarina::Render> render(new SoftRasterizer(model));
    return new Sandbox(render);
}

