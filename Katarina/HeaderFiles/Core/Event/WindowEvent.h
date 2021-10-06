#pragma once
#include "TypeDefines.h"
#include "Event.h"
#include <string>
#include <sstream>
namespace Katarina {


	class KATARINA_API WindowEvent :public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	public:
		WindowEvent(unsigned int width, unsigned int height)
			:m_width(width), m_height(height) {}
		_FORCE_INLINE_ unsigned int GetWidth()const
		{
			return m_width;
		}
		_FORCE_INLINE_ unsigned int GetHeight()const
		{
			return m_height;
		}
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "WindwowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}
	protected:
		unsigned int m_width, m_height;
	};



	class KATARINA_API WindowResizeEvent:public WindowEvent
	{
	public:
		EVENT_CLASS_TYPE(WindowResize)
		WindowResizeEvent(unsigned int width, unsigned int height)
			:WindowEvent(width,height){}
	private:
		unsigned int m_width, m_height;
	};

}

