#pragma once
#ifdef KT_PLATFORM_WINDWOS
#ifdef KT_BUILD_DLL
#define KATARINA_API _declspec(dllexport)
#else
#define KATARINA_API _declspec(dllimport)
#endif 
#else
#error  Katarina only support Windwos!
#endif

#ifndef _ALWAYS_INLINE_
#if defined(__GNUC__)
#define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define _ALWAYS_INLINE_ __forceinline
#else
#define _ALWAYS_INLINE_ inline
#endif
#endif

#ifndef _FORCE_INLINE_
#ifdef DISABLE_FORCED_INLINE
#define _FORCE_INLINE_ inline
#else
#define _FORCE_INLINE_ _ALWAYS_INLINE_
#endif
#endif


// core log macros
#define KT_CORE_ERROR(...) ::Katarina::Log::GetCoreLogger()->error(_VA_ARGS_)
#define KT_CORE_WARN(...)  ::Katarina::Log::GetCoreLogger()->warn(_VA_ARGS_)
#define KT_CORE_INFO(...)  ::Katarina::Log::GetCoreLogger()->info(_VA_ARGS_)
#define KT_CORE_TRACE(...) ::Katarina::Log::GetCoreLogger()->trace(_VA_ARGS_)
#define KT_CORE_FATAL(...) ::Katarina::Log::GetCoreLogger()->fatal(_VA_ARGS_)

// client log macros
#define KT_ERROR(...)	::Katarina::Log::GetClientLogger()->error(_VA_ARGS_)
#define KT_WARN(...)	::Katarina::Log::GetClientLogger()->warn(_VA_ARGS_)
#define KT_INFO(...)	::Katarina::Log::GetClientLogger()->info(_VA_ARGS_)
#define KT_TRACE(...)	::Katarina::Log::GetClientLogger()->trace(_VA_ARGS_)
#define KT_FATAL(...)	::Katarina::Log::GetClientLogger()->critical(_VA_ARGS_)

#define SHIFT_LEFT(x) (1<<(x))

#define real_t double


