//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_FUNCVECTOR2_HPP
#define VICTORIAM_FUNCVECTOR2_HPP

#include <ostream>

#include <Victoriam/Math/Vector/TypeVector2.hpp>

VISRCBEG

	VIDECL Bool operator==(const SVector2& a, const SVector2& b);
	VIDECL Bool operator!=(const SVector2& a, const SVector2& b);
	VIDECL Bool operator<=(const SVector2& a, const SVector2& b);
	VIDECL Bool operator>=(const SVector2& a, const SVector2& b);
	VIDECL Bool operator< (const SVector2& a, const SVector2& b);
	VIDECL Bool operator> (const SVector2& a, const SVector2& b);

	VIDECL SVector2 max(const SVector2& a, const SVector2& b);
	VIDECL SVector2 min(const SVector2& a, const SVector2& b);

	VIDECL Scalar FDot(const SVector2& a, const SVector2& b);
	VIDECL Scalar FSkew(const SVector2& a, const SVector2& b);
	VIDECL Scalar FCross(const SVector2& a, const SVector2& b);
	VIDECL Scalar FLength(const SVector2& a);
	VIDECL Scalar FLength2(const SVector2& a);
	VIDECL Scalar FDistance(const SVector2& from, const SVector2& to);
	VIDECL SVector2 FNormalize(const SVector2& a);
	VIDECL SVector2 FFloor(const SVector2& a);
	VIDECL SVector2 FCeil(const SVector2& a);
	VIDECL Scalar FMagnitude(const SVector2& a);
	VIDECL Scalar FRMagnitude(const SVector2& a);

	VIDECL std::ostream& operator<<(std::ostream& os, const SVector2& v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR2_HPP
