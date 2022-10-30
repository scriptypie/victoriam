//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#ifndef VICTORIAM_UJOBWORKER_HPP
#define VICTORIAM_UJOBWORKER_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

class VIDECL CJobWorker
{
	std::thread m_WorkingThread = {};
public:
	inline CJobWorker() = default;
	inline ~CJobWorker() { Join(); }

	template<class T, class Fn = std::function<void(T&, const String&)>>
	VIDECL inline CJobWorker(T& data, const String filename, Fn fn)
	{
		m_WorkingThread = std::thread([&data, filename, &fn]() { fn(data, filename); });
	}

	template<class T, class Fn = std::function<void(T&, const String&)>>
	VIDECL inline void operator()(T& data, const String filename, Fn fn)
	{
		m_WorkingThread = std::thread([&data, filename, &fn]() { fn(data, filename); });
	}

	VIDECL void Join();

};

VISRCEND

#endif //VICTORIAM_UJOBWORKER_HPP
