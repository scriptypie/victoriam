//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EWINDOWEVENTS_HPP
#define VICTORIAM_EWINDOWEVENTS_HPP

#include <Victoriam/EventSystem/EEvent.hpp>

VISRCBEG

/**
 * Event that signaled about main window close
 */
class VIDECL CWindowCloseEvent : public CEvent
{
public:
	inline CWindowCloseEvent() = default;

	VIDECL VIREQOUT String ToString() const override
	{
		CStream ss;
		ss << "CWindowCloseEvent()";
		return ss.Str();
	}

	EVENT_CLASS_TYPE(WindowClosed)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/**
 * Event that signaled about window resizing, and contains additional information.
 */
class VIDECL CWindowResizeEvent : public CEvent
{
	UInt32 m_Width, m_Height;
public:
	CWindowResizeEvent(UInt32 width, UInt32 height) : m_Width(width), m_Height(height) {}
	/**
	 * Access to new window's width.
	 */
	VIDECL VIREQOUT inline UInt32 GetWidth() const { return m_Width; }
	/**
	 * Access to new window's height.
	 */
	VIDECL VIREQOUT inline UInt32 GetHeight() const { return m_Height; }
	/**
	 * Access to new window's width and height as extent.
	 */
	VIDECL VIREQOUT inline SExtent2D GetExtent() const { return {m_Width, m_Height }; }

	VIDECL VIREQOUT String ToString() const override
	{
		CStream ss;
		ss << "CWindowResizeEvent(" << m_Width << ", " << m_Height << ")";
		return ss.Str();
	}

	EVENT_CLASS_TYPE(WindowResized)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/**
 * Called every time when main window lost focus.
 */
class VIDECL CWindowLostFocusEvent : public CEvent
{
public:
	inline CWindowLostFocusEvent() = default;

	VIDECL VIREQOUT String ToString() const override
	{
		CStream ss;
		ss << "CWindowLostFocusEvent()";
		return ss.Str();
	}

	EVENT_CLASS_TYPE(WindowLostFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/**
 * Called every time when main window gets in focus by cursor.
 */
class VIDECL CWindowGetFocusEvent : public CEvent
{
public:
	inline CWindowGetFocusEvent() = default;

	VIDECL VIREQOUT String ToString() const override
	{
		CStream ss;
		ss << "CWindowGetFocusEvent()";
		return ss.Str();
	}

	EVENT_CLASS_TYPE(WindowGetFocus)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


VISRCEND

#endif //VICTORIAM_EWINDOWEVENTS_HPP
