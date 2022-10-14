//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EVENT_HPP
#define VICTORIAM_EVENT_HPP

#include <Victoriam/Core/Base.hpp>

VISRCBEG

enum class ecEventType : UInt32
{
	None = 0,
	WindowClosed,       WindowResized,      WindowLostFocus,        WindowGetFocus,
	KeyboardButtonDown, KeyboardButtonUp,   KeyboardButtonTyped,
	MouseMoved,         MouseButtonDown,    MouseButtonUp,          MouseScrolled
};

typedef UInt32  EventCategory;
constexpr       EventCategory None = 0x00000000;
constexpr       EventCategory EventCategoryApplication    = 0x00000001;
constexpr       EventCategory EventCategoryInput          = 0x00000010;
constexpr       EventCategory EventCategoryKeyboard       = 0x00000100;
constexpr       EventCategory EventCategoryMouse          = 0x00001000;
constexpr       EventCategory EventCategoryMouseButton    = 0x00010000;

// Helper macros only for event system internal usage

#define EVENT_CLASS_TYPE(type) \
	inline static ecEventType GetStaticType() { return ecEventType::type; } \
	inline ecEventType GetEventType() const override { return GetStaticType(); } \
	inline CString GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(cat) \
	inline EventCategory GetCategoryFlags() const override { return cat; }

// end helpers

class cEvent
{
public:
	virtual ~cEvent() = default;

	Bool m_Handled = false;

	virtual ecEventType GetEventType() const = 0;
	virtual CString GetName() const = 0;
	virtual EventCategory GetCategoryFlags() const = 0;
	virtual String ToString() const { return GetName(); }
	Bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}
};

VISRCEND

#endif //VICTORIAM_EVENT_HPP
