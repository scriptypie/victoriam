//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_MINMAX_HPP
#define VICTORIAM_MINMAX_HPP

#include <Victoriam/Math/Common/Scalar.hpp>

VISRCBEG

VIDECL inline constexpr Scalar fMin(const Scalar& a, const Scalar& b)
{
	if (a == b) return a;
	return (a < b) ? a : b;
}

VIDECL inline constexpr Scalar fMax(const Scalar& a, const Scalar& b)
{
	if (a == b) return a;
	return (a > b) ? a : b;
}

VISRCEND

#endif //VICTORIAM_MINMAX_HPP
