#include "Katarina.h"
#include "Render/Render.h"
#include "Render/RayTracing/RayTracing.h"
#include "Render/Scene/RayTracingScene.h"
#include <memory>
class Sandbox :public Katarina::Application
{
public:
	Sandbox(std::shared_ptr<Katarina::Render> r) :Application(r) {}
	virtual ~Sandbox() {}
};

Katarina::Application* Katarina::CreateApplication()
{
	std::shared_ptr<Katarina::Scene> scene(new Katarina::RayTracingScene);
	// Camera
	Vector3 lookfrom(13, 2, 3);	// �����Դ��
	Vector3 lookat(0, 0, 0);	// �����Ŀ��
	Vector3 vup(0, 1, 0);		// ��������
	// ��Ȧ���Ӿ�����ʵ���˶�ģ��
	auto dist_to_focus = 10.0;	// �Ӿ�			
	auto aperture = 0.1;	// ��Ȧ
	const auto aspectRatio = 3.0 / 2.0;
	Camera camera(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);

	std::shared_ptr<Katarina::Render> render(new RayTracing(camera, scene, 50));
	return new Sandbox(render);
}

