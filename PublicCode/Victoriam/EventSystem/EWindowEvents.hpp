//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EWINDOWEVENTS_HPP
#define VICTORIAM_EWINDOWEVENTS_HPP

#include <Victoriam/EventSystem/EEvent.hpp>

VISRCBEG

class CWindowCloseEvent : public CEvent
{
public:
	inline CWindowCloseEvent() = default;

	VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowCloseEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowClosed)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class CWindowResizeEvent : public CEvent
{
	UInt32 m_Width, m_Height;
public:
	CWindowResizeEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}

	VIREQOUT inline UInt32 GetWidth() const { return m_Width; }
	VIREQOUT inline UInt32 GetHeight() const { return m_Height; }
	VIREQOUT inline SWindowExtent GetExtent() const { return {m_Width, m_Height }; }

	VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowResizeEvent(" << m_Width << ", " << m_Height << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResized)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class CWindowLostFocusEvent : public CEvent
{
public:
	inline CWindowLostFocusEvent() = default;

	VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowLostFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class CWindowGetFocusEvent : public CEvent
{
public:
	inline CWindowGetFocusEvent() = default;

	VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowGetFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowGetFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


VISRCEND

#endif //VICTORIAM_EWINDOWEVENTS_HPP
