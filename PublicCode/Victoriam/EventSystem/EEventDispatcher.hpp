//
// Created by Вячеслав Кривенко on 10.10.2022.
//

#ifndef VICTORIAM_EEVENTDISPATCHER_HPP
#define VICTORIAM_EEVENTDISPATCHER_HPP

#include <Victoriam/EventSystem/EEvent.hpp>

VISRCBEG

class cEventDispatcher
{
	cEvent& m_Event;
public:
	inline explicit cEventDispatcher(cEvent& event) : m_Event(event) {}

	template<class T, class FN>
	inline Bool Dispatch(const FN& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
};

inline std::ostream& operator<<(std::ostream& os, const cEvent& event)
{
	return os << event.ToString();
}

VISRCEND

#endif //VICTORIAM_EEVENTDISPATCHER_HPP
