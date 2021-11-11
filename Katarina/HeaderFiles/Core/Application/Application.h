#pragma once
#include "TypeDefines.h"
#include <memory>
namespace Katarina {
	class Render;
	class KATARINA_API Application
	{
	public:
		Application(std::shared_ptr<Render> r) :render(r) {}
		virtual ~Application() {}
		void Run();
	private:
		std::shared_ptr<Render> render;
	};

	Application* CreateApplication();
}

