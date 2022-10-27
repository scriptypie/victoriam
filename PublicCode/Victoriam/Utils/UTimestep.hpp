//
// Created by Вячеслав Кривенко on 27.10.2022.
//

#ifndef VICTORIAM_UTIMESTEP_HPP
#define VICTORIAM_UTIMESTEP_HPP

#include <Victoriam/Core/CBase.hpp>

#include <chrono>

VISRCBEG

class VIDECL CTimestep
{
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
public:
	VIDECL CTimestep() : m_Start(std::chrono::high_resolution_clock::now()) {}
	VIDECL VIREQOUT Float32 Delta() const
	{
		return CCast<Float32>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count()) * 0.001f * 0.001f * 0.001f;
	}
	VIDECL VIREQOUT Float32 DeltaMilli() const
	{
		return Delta() * 1000.0F;
	}
};

VISRCEND

#endif //VICTORIAM_UTIMESTEP_HPP
