#pragma once
#include "Core.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication(); // 由用户定义的CreateApplication()函数，返回一个 Hazel::Application 的实例

}