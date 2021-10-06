#pragma once
#include "TypeDefines.h"
#include "Event.h"
#include <sstream>
namespace Katarina {
	class KATARINA_API MouseEvent:public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryMouse|EventCategoryInput )
	public:
		MouseEvent(real_t x,real_t y):m_MouseX(x), m_MouseY(y){}
		_FORCE_INLINE_ real_t GetX()const { return m_MouseX; }
		_FORCE_INLINE_ real_t GetY()const { return m_MouseY; }
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str(); 
		}
	protected:
		real_t m_MouseX, m_MouseY;
	};

	class KATARINA_API MouseMovedEvent :public MouseEvent
	{
		EVENT_CLASS_TYPE(MouseMoved)
	public:
		using MouseEvent::MouseEvent;
	};


}