#pragma once
#include "Core/Application/Application.h"
#include "Core/Log/Log.h"
#ifdef KT_PLATFORM_WINDWOS

extern Katarina::Application* Katarina::CreateApplication();

int main(int argc, char** argv)
{
	Katarina::Log::Init();
	auto app = Katarina::CreateApplication();
	app->Run();
	delete app;
}

#endif