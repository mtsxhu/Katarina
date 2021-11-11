#include "Core/Application/Application.h"
#include "Render/Render.h"
#include "Render/RayTracing/RayTracing.h"
namespace Katarina
{
	void Application::Run()
	{
		this->render->run();
	}
}