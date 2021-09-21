#pragma once
#include "TypeDefines.h"
namespace Katarina {
	class KATARINA_API Application
	{
	public:
		Application() = default;
		virtual ~Application(){}
		void Run();
	};

	// TO be defined in client
	Application* CreateApplication();
}

