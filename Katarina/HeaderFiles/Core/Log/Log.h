#pragma once
#include "TypeDefines.h"
#include "spdlog/spdlog.h"
namespace Katarina {

	class KATARINA_API Log
	{
	public:
		static void Init();
		_FORCE_INLINE_ static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		_FORCE_INLINE_ static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

