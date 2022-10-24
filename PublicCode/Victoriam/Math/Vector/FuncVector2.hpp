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

	VIDECL Scalar fDot(const SVector2& a, const SVector2& b);
	VIDECL Scalar fSkew(const SVector2& a, const SVector2& b);
	VIDECL Scalar fCross(const SVector2& a, const SVector2& b);
	VIDECL Scalar fLength(const SVector2& a);
	VIDECL Scalar fLength2(const SVector2& a);
	VIDECL Scalar fDistance(const SVector2& from, const SVector2& to);
	VIDECL SVector2 fNormalize(const SVector2& a);
	VIDECL SVector2 fFloor(const SVector2& a);
	VIDECL SVector2 fCeil(const SVector2& a);
	VIDECL Scalar fMagnitude(const SVector2& a);
	VIDECL Scalar fRMagnitude(const SVector2& a);

	VIDECL std::ostream& operator<<(std::ostream& os, const SVector2& v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR2_HPP
