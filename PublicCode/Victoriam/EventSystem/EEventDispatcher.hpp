//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EEVENTDISPATCHER_HPP
#define VICTORIAM_EEVENTDISPATCHER_HPP

#include <Victoriam/EventSystem/EEvent.hpp>

VISRCBEG

class VIDECL CEventDispatcher
{
	CEvent& m_Event;
public:
	VIDECL inline explicit CEventDispatcher(CEvent& event) : m_Event(event) {}

	template<class T, class FN>
	VIDECL inline Bool Dispatch(const FN& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
};

VIDECL inline std::ostream& operator<<(std::ostream& os, const CEvent& event)
{
	return os << event.ToString();
}

VISRCEND

#endif //VICTORIAM_EEVENTDISPATCHER_HPP
