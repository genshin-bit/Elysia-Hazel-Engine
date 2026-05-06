#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.
	// Hazel 引擎中的事件目前是阻塞式的，这意味着事件一旦发生，就会被立即分发，且必须当场、立即处理完毕。
	// 未来更优的策略或许是将事件暂存（缓冲）到事件总线中，然后在引擎更新阶段的 “事件处理环节” 统一处理它们。

	enum class EventType
	{
		None = 0,
		//窗口类事件
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		//应用程序生命周期类事件
		AppTick, AppUpdate, AppRender,
		//键盘类事件
		KeyPressed, KeyReleased,
		//鼠标类事件
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// EventCategory：事件分类枚举（位掩码设计）
	// 作用：按“功能维度”给事件打标签，一个事件可同时属于多个分类；
	//		 配合位运算（&、|）可快速判断“事件是否属于某类”，实现批量过滤。
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0), //应用程序类事件
		EventCategoryInput = BIT(1),       //输入类事件
		EventCategoryKeyboard = BIT(2),    //键盘类事件
		EventCategoryMouse = BIT(3),       //鼠标类事件
		EventCategoryMouseButton = BIT(4)  //鼠标按键类事件
	};

	// 事件类的宏定义：给具体的事件类自动生成 3 个与 “事件类型标识” 相关的函数,简化事件类的编写
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// 事件分类的宏定义：给具体的事件类自动重写 GetCategoryFlags 虚函数,简化事件类的编写
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
		friend class EventDispatcher;								  
	public:
		virtual EventType GetEventType() const = 0;                   //纯虚函数：获取事件类型
		virtual const char* GetName() const = 0;					  //纯虚函数：获取事件名称
		virtual int GetCategoryFlags() const = 0;					  //纯虚函数：获取事件分类标志（位掩码）
		virtual std::string ToString() const { return GetName(); }	  //虚函数：获取事件的字符串表示，默认为事件名称

		inline bool IsInCategory(EventCategory category)			  //内联函数：判断事件是否属于某个分类
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	// 事件分发器类：用于将事件分发给相应的事件处理函数
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
