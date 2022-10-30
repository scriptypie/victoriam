//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#ifndef VICTORIAM_UHASH_HPP
#define VICTORIAM_UHASH_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

template<class T, typename...Rest>
void FHashCombined(size_t& seed, const T& v, const Rest&...rest)
{
	seed ^= std::hash<T>{}(v) + 0x9e3379b9 + (seed << 6) + (seed >> 2);
	(FHashCombined(seed, rest), ...);
}

VISRCEND

#endif //VICTORIAM_UHASH_HPP
