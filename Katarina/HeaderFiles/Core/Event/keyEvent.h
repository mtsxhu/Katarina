#pragma once
#include "Event.h"
#include "TypeDefines.h"
#include <sstream>
namespace Katarina {
	class KATARINA_API KeyEvent :public Event
	{
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard|EventCategory::EventCategoryInput)
	public:
		KeyEvent(int keycode) :m_KeyCode(keycode) {}
		_FORCE_INLINE_ int GetKeyCode()const { return m_KeyCode; }
	protected:
		int m_KeyCode;
	};

	class KATARINA_API KeyPressedEvent :public KeyEvent
	{
		EVENT_CLASS_TYPE(KeyPressed)
	public:
		using KeyEvent::KeyEvent;
		KeyPressedEvent(int keycode, int repeatCount) :KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		_FORCE_INLINE_ int GetRepeatCount()const { return m_RepeatCount; }
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType()const override { return GetStaticType(); }
		virtual const char* GetName()const override { return "KeyPressed"; }
	private:
		int m_RepeatCount;
	};
}


