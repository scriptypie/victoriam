//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_WINDOWEVENTS_HPP
#define VICTORIAM_WINDOWEVENTS_HPP

#include <Victoriam/EventSystem/Event.hpp>

VISRCBEG

class cWindowCloseEvent : public cEvent
{
public:
	cWindowCloseEvent() {}

	String ToString() const override
	{
		StringStream ss;
		ss << "cWindowCloseEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowClosed)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class cWindowResizeEvent : public cEvent
{
	UInt32 m_Width, m_Height;
public:
	cWindowResizeEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}

	inline UInt32 GetWidth() const { return m_Width; }
	inline UInt32 GetHeight() const { return m_Height; }

	String ToString() const override
	{
		StringStream ss;
		ss << "cWindowResizeEvent(" << m_Width << ", " << m_Height << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResized)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class cWindowLostFocusEvent : public cEvent
{
public:
	cWindowLostFocusEvent() {}

	String ToString() const override
	{
		StringStream ss;
		ss << "cWindowLostFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class cWindowGetFocusEvent : public cEvent
{
public:
	cWindowGetFocusEvent() {}

	String ToString() const override
	{
		StringStream ss;
		ss << "cWindowGetFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowGetFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


VISRCEND

#endif //VICTORIAM_WINDOWEVENTS_HPP
