//
// Created by Вячеслав Кривенко on 11.10.2022.
//

#ifndef VICTORIAM_CCAST_HPP
#define VICTORIAM_CCAST_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

/**
 * Evil-hack style cast
 */
template<class To, class From>
VIDECL inline constexpr To& Cast(const From& from)
{
	return *(To*)from;
}

/**
 * C-Style cast
 */
template<class To, class From>
VIDECL inline constexpr To CCast(const From& from)
{
	return (To)(from);
}

VISRCEND

#endif //VICTORIAM_CCAST_HPP
