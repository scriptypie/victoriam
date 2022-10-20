//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EWINDOWEVENTS_HPP
#define VICTORIAM_EWINDOWEVENTS_HPP

#include <Victoriam/EventSystem/EEvent.hpp>

VISRCBEG

class cWindowCloseEvent : public cEvent
{
public:
	inline cWindowCloseEvent() = default;

	VIREQOUT String ToString() const override
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

	VIREQOUT inline UInt32 GetWidth() const { return m_Width; }
	VIREQOUT inline UInt32 GetHeight() const { return m_Height; }
	VIREQOUT inline sWindowExtent GetExtent() const { return { m_Width, m_Height }; }

	VIREQOUT String ToString() const override
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
	inline cWindowLostFocusEvent() = default;

	VIREQOUT String ToString() const override
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
	inline cWindowGetFocusEvent() = default;

	VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "cWindowGetFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowGetFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


VISRCEND

#endif //VICTORIAM_EWINDOWEVENTS_HPP
