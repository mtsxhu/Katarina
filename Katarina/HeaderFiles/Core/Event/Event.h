#pragma once
#include "TypeDefines.h"
#include <string>
#include<functional>

namespace Katarina {
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	// 不用enum class 是为了用位操作符
	enum  EventCategory
	{
	
		None = 0,
		EventCategoryWindow = SHIFT_LEFT(0),
		EventCategoryInput = SHIFT_LEFT(1),
		EventCategoryKeyboard = SHIFT_LEFT(2),
		EventCategoryMouse = SHIFT_LEFT(3),
		EventCategoryMouseButton = SHIFT_LEFT(4)
	};

	class KATARINA_API Event
	{
	public:
		virtual EventType GetEventType()const = 0;
		virtual const char* GetName()const = 0;
		virtual int GetCategoryFlags()const = 0;
		virtual std::string ToString()const { return GetName(); };
		_FORCE_INLINE_ bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_handled;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :m_Event(event) {};
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType()==T::GetStaticType())
			{
				m_Event.m_handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	_FORCE_INLINE_ std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

#define EVENT_CLASS_TYPE(type)\
public:\
	static EventType GetStaticType(){return EventType::##type;}\
	virtual EventType GetEventType()const override {return GetStaticType();}\
	virtual const char* GetName()const override {return #type;}

#define EVENT_CLASS_CATEGORY(category)\
public:\
	virtual int GetCategoryFlags()const override {return category;}
}
