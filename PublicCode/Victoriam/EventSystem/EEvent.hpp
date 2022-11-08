//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EEVENT_HPP
#define VICTORIAM_EEVENT_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

enum class VIDECL ECEventType : UInt32
{
	None = 0,
	WindowClosed,       WindowResized,      WindowLostFocus,        WindowGetFocus,
	KeyboardButtonDown, KeyboardButtonUp,   KeyboardButtonTyped,
	MouseMoved,         MouseButtonDown,    MouseButtonUp,          MouseScrolled
};

VIDECL typedef UInt32 EventCategory;
VIDECL constexpr       EventCategory None                        = 0x00000000;
VIDECL constexpr       EventCategory EventCategoryApplication    = 0x00000001;
VIDECL constexpr       EventCategory EventCategoryInput          = 0x00000010;
VIDECL constexpr       EventCategory EventCategoryKeyboard       = 0x00000100;
VIDECL constexpr       EventCategory EventCategoryMouse          = 0x00001000;
VIDECL constexpr       EventCategory EventCategoryMouseButton    = 0x00010000;

// Helper macros only for event system internal usage

#define EVENT_CLASS_TYPE(type) \
	VIDECL VIREQOUT inline static ECEventType GetStaticType() { return ECEventType::type; } \
	VIDECL VIREQOUT inline ECEventType GetEventType() const override { return GetStaticType(); } \
	VIDECL VIREQOUT inline CString GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(cat) \
	VIDECL VIREQOUT inline EventCategory GetCategoryFlags() const override { return cat; }

// end helpers

class VIDECL CEvent
{
public:
	VIDECL virtual ~CEvent() = default;

	Bool m_Handled = false;

	VIDECL VIREQOUT virtual ECEventType GetEventType() const = 0;
	VIDECL VIREQOUT virtual CString GetName() const = 0;
	VIDECL VIREQOUT virtual EventCategory GetCategoryFlags() const = 0;
	VIDECL VIREQOUT virtual String ToString() const { return GetName(); }
	VIDECL VIREQOUT Bool IsInCategory(EventCategory category) const
	{
		return GetCategoryFlags() & category;
	}
};

VISRCEND

#endif //VICTORIAM_EEVENT_HPP
