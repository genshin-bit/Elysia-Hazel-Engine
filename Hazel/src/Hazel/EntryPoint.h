#pragma once

#ifdef HZ_PLATFORM_WINDOWS

/*
 Entry Point 入口点
 由平台特定的入口点实现文件（如 src/Hazel/EntryPoint.h）包含，定义了应用程序的入口点
 该文件包含了 Hazel 应用程序的核心功能，并且通过用户定义的 CreateApplication() 函数创建应用程序实例
 例如，在 Windows 平台上，EntryPoint.h 文件会定义 main 函数，调用 CreateApplication() 来创建应用程序实例并运行它
 通过包含 Hazel.h，用户的应用程序可以访问 Hazel 的核心功能，并且通过实现 CreateApplication() 函数来创建和运行他们的应用程序实例
 例如，在 Sandbox 应用程序中，用户会实现 CreateApplication() 函数来返回一个新的 Sandbox 实例，这样当应用程序运行时，就会创建并运行 Sandbox 应用程序实例
 */

extern Hazel::Application* Hazel::CreateApplication(); // 由用户定义的CreateApplication()函数，返回一个 Hazel::Application 的实例

int main(int argc,char** argv) {
	Hazel::Log::Init(); // 初始化日志系统
	HZ_CORE_WARN("Initialized Log!"); // 记录一条日志，使用核心日志记录器输出警告级别的消息 "日志完成初始化" 
	HZ_INFO("Hello");

	auto app = Hazel::CreateApplication(); // 创建应用程序实例
	app->Run();
	delete app;
}
#endif
