//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EEVENT_HPP
#define VICTORIAM_EEVENT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/IO/IOStream.hpp>

VISRCBEG

/**
 * Enum class of event type.
 */
enum class VIDECL ECEventType : UInt32
{
	None = 0,
	WindowClosed,       WindowResized,      WindowLostFocus,        WindowGetFocus,
	KeyboardButtonDown, KeyboardButtonUp,   KeyboardButtonTyped,
	MouseMoved,         MouseButtonDown,    MouseButtonUp,          MouseScrolled
};

Constant<Signal, 0x00000001> EventCategoryApplication;
Constant<Signal, 0x00000010> EventCategoryInput;
Constant<Signal, 0x00000100> EventCategoryKeyboard;
Constant<Signal, 0x00001000> EventCategoryMouse;
Constant<Signal, 0x00010000> EventCategoryMouseButton;

// Helper macros only for event system internal usage

#define EVENT_CLASS_TYPE(type) \
	VIDECL VIREQOUT inline static ECEventType GetStaticType() { return ECEventType::type; } \
	VIDECL VIREQOUT inline ECEventType GetEventType() const override { return GetStaticType(); } \
	VIDECL VIREQOUT inline CString GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(cat) \
	VIDECL VIREQOUT inline Signal GetCategoryFlags() const override { return cat; }

// end helpers

class VIDECL CEvent
{
public:
	VIDECL virtual ~CEvent() = default;

	Bool m_Handled = false;

	VIDECL VIREQOUT virtual ECEventType GetEventType() const = 0;
	VIDECL VIREQOUT virtual CString GetName() const = 0;
	VIDECL VIREQOUT virtual Signal GetCategoryFlags() const = 0;
	VIDECL VIREQOUT virtual String ToString() const { return GetName(); }
	VIDECL VIREQOUT Bool IsInCategory(Signal category) const
	{
		return GetCategoryFlags() & category;
	}
};

VISRCEND

#endif //VICTORIAM_EEVENT_HPP
