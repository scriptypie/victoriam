//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_KEYBOARDEVENTS_HPP
#define VICTORIAM_KEYBOARDEVENTS_HPP

#include <Victoriam/EventSystem/Event.hpp>
#include <Victoriam/Input/Keycode.hpp>

VISRCBEG

class cKeyboardEvent : public cEvent
{
protected:
	eKeyboardCode m_Code;

	cKeyboardEvent(const eKeyboardCode& code) : m_Code(code) {}
public:
	inline eKeyboardCode GetKeyboardCode() const { return m_Code; }

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
};

class cKeyboardButtonDownEvent : public cKeyboardEvent
{
	Bool m_IsRepeat;
public:
	cKeyboardButtonDownEvent(const eKeyboardCode& key, const Bool is_repeat = (Bool)0)
			: cKeyboardEvent(key), m_IsRepeat(is_repeat)
	{}

	inline Bool IsRepeat() const { return m_IsRepeat; }

	String ToString() const override
	{
		StringStream ss;
		ss << "cKeyboardButtonDownEvent: " << m_Code << " (is_repeat=" << m_IsRepeat << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyboardButtonDown)
};

class cKeyboardButtonUpEvent : public cKeyboardEvent
{
public:
	cKeyboardButtonUpEvent(const eKeyboardCode& key)
			: cKeyboardEvent(key)
	{}

	String ToString() const override
	{
		StringStream ss;
		ss << "cKeyboardButtonUpEvent: " << m_Code << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyboardButtonUp)
};

class cKeyboardInputEvent : public cKeyboardEvent
{
public:
	cKeyboardInputEvent(const eKeyboardCode& key)
			: cKeyboardEvent(key)
	{}

	String ToString() const override
	{
		StringStream ss;
		ss << "cKeyboardInputEvent: " << m_Code << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyboardButtonTyped)
};

VISRCEND

#endif //VICTORIAM_KEYBOARDEVENTS_HPP
