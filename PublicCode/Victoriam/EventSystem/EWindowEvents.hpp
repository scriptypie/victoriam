//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EWINDOWEVENTS_HPP
#define VICTORIAM_EWINDOWEVENTS_HPP

#include <Victoriam/EventSystem/EEvent.hpp>
#include <Victoriam/Graphics/Structs/GWindowExtent.hpp>

VISRCBEG

class VIDECL CWindowCloseEvent : public CEvent
{
public:
	inline CWindowCloseEvent() = default;

	VIDECL VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowCloseEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowClosed)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class VIDECL CWindowResizeEvent : public CEvent
{
	UInt32 m_Width, m_Height;
public:
	CWindowResizeEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}

	VIDECL VIREQOUT inline UInt32 GetWidth() const { return m_Width; }
	VIDECL VIREQOUT inline UInt32 GetHeight() const { return m_Height; }
	VIDECL VIREQOUT inline SWindowExtent GetExtent() const { return {m_Width, m_Height }; }

	VIDECL VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowResizeEvent(" << m_Width << ", " << m_Height << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResized)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class VIDECL CWindowLostFocusEvent : public CEvent
{
public:
	inline CWindowLostFocusEvent() = default;

	VIDECL VIREQOUT String ToString() const override
	{
		StringStream ss;
		ss << "CWindowLostFocusEvent()";
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class VIDECL CWindowGetFocusEvent : public CEvent
{
public:
	inline CWindowGetFocusEvent() = default;

	VIDECL VIREQOUT String ToString() const override
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
