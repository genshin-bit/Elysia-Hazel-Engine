#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"


namespace Hazel
{
	class HAZEL_API Log
	{
	public:
		static void Init();
		// 获取核心日志记录器的静态成员函数，返回一个指向 spdlog::logger 的共享指针
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		// 获取客户端日志记录器的静态成员函数，返回一个指向 spdlog::logger 的共享指针
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; // 核心日志记录器的静态成员变量，存储一个指向 spdlog::logger 的共享指针
		static std::shared_ptr<spdlog::logger> s_ClientLogger; // 客户端日志记录器的静态成员变量，存储一个指向 spdlog::logger 的共享指针
	};
}

//核心日志宏定义，使用核心日志记录器输出不同级别的日志消息
#define HZ_CORE_ERROR(...)  ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_WARN(...)   ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_INFO(...)   ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_TRACE(...)  ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_FATAL(...)  ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//客户端日志宏定义，使用客户端日志记录器输出不同级别的日志消息
#define HZ_ERROR(...)  ::Hazel::Log::GetClientLogger->error(__VA_ARGS__)
#define HZ_WARN(...)   ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_INFO(...)   ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_TRACE(...)  ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_FATAL(...)  ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)



