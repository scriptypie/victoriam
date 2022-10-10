//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_FUNCVECTOR2_HPP
#define VICTORIAM_FUNCVECTOR2_HPP

#include <ostream>

#include <Victoriam/Math/Vector/TypeVector2.hpp>

VISRCBEG

	VIDECL inline Bool operator==(const sVector2& a, const sVector2& b);
	VIDECL inline Bool operator!=(const sVector2& a, const sVector2& b);
	VIDECL inline Bool operator<=(const sVector2& a, const sVector2& b);
	VIDECL inline Bool operator>=(const sVector2& a, const sVector2& b);
	VIDECL inline Bool operator< (const sVector2& a, const sVector2& b);
	VIDECL inline Bool operator> (const sVector2& a, const sVector2& b);

	VIDECL inline sVector2 max(const sVector2& a, const sVector2& b);
	VIDECL inline sVector2 min(const sVector2& a, const sVector2& b);

	VIDECL inline Scalar fDot(const sVector2& a, const sVector2& b);
	VIDECL inline Scalar fSkew(const sVector2& a, const sVector2& b);
	VIDECL inline Scalar fCross(const sVector2& a, const sVector2& b);
	VIDECL inline Scalar fLength(const sVector2& a);
	VIDECL inline Scalar fLength2(const sVector2& a);
	VIDECL inline Scalar fDistance(const sVector2& from, const sVector2& to);
	VIDECL inline sVector2 fNormalize(const sVector2& a);
	VIDECL inline sVector2 fFloor(const sVector2& a);
	VIDECL inline sVector2 fCeil(const sVector2& a);
	VIDECL inline Scalar fMagnitude(const sVector2& a);
	VIDECL inline Scalar fRMagnitude(const sVector2& a);

	VIDECL inline std::ostream& operator<<(std::ostream& os, const sVector2& v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR2_HPP
