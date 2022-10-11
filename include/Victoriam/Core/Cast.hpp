//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_CAST_HPP
#define VICTORIAM_CAST_HPP

#include <Victoriam/Core/MacroDefinitions.hpp>

VISRCBEG

template<class To, class From>
VIDECL inline constexpr To& Cast(const From& from)
{
	return *(To*)from;
}

template<class To, class From>
VIDECL inline constexpr To CCast(const From& from)
{
	return (To)(from);
}

VISRCEND

#endif //VICTORIAM_CAST_HPP
