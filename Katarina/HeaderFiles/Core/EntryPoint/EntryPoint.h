#pragma once

#ifdef KT_PLATFORM_WINDWOS

extern Katarina::Application* Katarina::CreateApplication();

int main(int argc,char** argv)
{
	Katarina::Log::Init();
	Katarina::Log::GetCoreLogger()->warn("Initialized Log!");
	Katarina::Log::GetClientLogger()->info("Hello!");
	auto app = Katarina::CreateApplication();
	app->Run();
	delete app;
}

#endif