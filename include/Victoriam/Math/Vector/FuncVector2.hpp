//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_FUNCVECTOR2_HPP
#define VICTORIAM_FUNCVECTOR2_HPP

#include <ostream>

#include <Victoriam/Math/Vector/TypeVector2.hpp>

VISRCBEG

	VIDECL Bool operator==(const sVector2& a, const sVector2& b);
	VIDECL Bool operator!=(const sVector2& a, const sVector2& b);
	VIDECL Bool operator<=(const sVector2& a, const sVector2& b);
	VIDECL Bool operator>=(const sVector2& a, const sVector2& b);
	VIDECL Bool operator< (const sVector2& a, const sVector2& b);
	VIDECL Bool operator> (const sVector2& a, const sVector2& b);

	VIDECL sVector2 max(const sVector2& a, const sVector2& b);
	VIDECL sVector2 min(const sVector2& a, const sVector2& b);

	VIDECL Scalar fDot(const sVector2& a, const sVector2& b);
	VIDECL Scalar fSkew(const sVector2& a, const sVector2& b);
	VIDECL Scalar fCross(const sVector2& a, const sVector2& b);
	VIDECL Scalar fLength(const sVector2& a);
	VIDECL Scalar fLength2(const sVector2& a);
	VIDECL Scalar fDistance(const sVector2& from, const sVector2& to);
	VIDECL sVector2 fNormalize(const sVector2& a);
	VIDECL sVector2 fFloor(const sVector2& a);
	VIDECL sVector2 fCeil(const sVector2& a);
	VIDECL Scalar fMagnitude(const sVector2& a);
	VIDECL Scalar fRMagnitude(const sVector2& a);

	VIDECL std::ostream& operator<<(std::ostream& os, const sVector2& v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR2_HPP
