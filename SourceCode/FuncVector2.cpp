//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#include <Victoriam/Math/Common/Comparator.hpp>

#include <Victoriam/Math/Vector/FuncVector2.hpp>

VISRCBEG

Bool operator==(const SVector2 &a, const SVector2 &b) {
	return
			(
					cComparator::Equal(a.data[0], b.data[0]) &&
					cComparator::Equal(a.data[1], b.data[1])
			);
}

Bool operator!=(const SVector2 &a, const SVector2 &b) {
	return
			(
					!cComparator::Equal(a.data[0], b.data[0]) ||
					!cComparator::Equal(a.data[1], b.data[1])
			);
}

Bool operator<=(const SVector2 &a, const SVector2 &b) {
	return
			(
					a.data[0] < b.data[0] &&
					a.data[1] <= b.data[1]
			);
}

Bool operator>=(const SVector2 &a, const SVector2 &b) {
	return
			(
					a.data[0] >= b.data[0] &&
					a.data[1] >= b.data[1]
			);
}

Bool operator<(const SVector2 &a, const SVector2 &b) {
	return
			(
					cComparator::Less(a.data[0], b.data[0]) &&
					cComparator::Less(a.data[1], b.data[1])
			);
}

Bool operator>(const SVector2 &a, const SVector2 &b) {
	return
			(
					cComparator::Greater(a.data[0], b.data[0]) &&
					cComparator::Greater(a.data[1], b.data[1])
			);
}

SVector2 max(const SVector2 &a, const SVector2 &b) {
	return (a > b) ? a : b;
}

SVector2 min(const SVector2 &a, const SVector2 &b) {
	return (a < b) ? a : b;
}

Scalar fDot(const SVector2 &a, const SVector2 &b) {
	return a.x * b.x + a.y * b.y;
}

Scalar fSkew(const SVector2 &a, const SVector2 &b) {
	return fCross(a, b);
}

Scalar fCross(const SVector2 &a, const SVector2 &b) {
	return a.x * b.y - a.y * b.x;
}

Scalar fLength(const SVector2 &a) {
	return
			(
					std::sqrtf(
							a.data[0] * a.data[0] +
							a.data[1] * a.data[1]
					)
			);
}

Scalar fLength2(const SVector2 &a) {
	return fLength(a) * fLength(a);
}

Scalar fDistance(const SVector2 &from, const SVector2 &to) {
	return fLength(
			{
	                   to.data[0] - from.data[0],
	                   to.data[1] - from.data[1]
               });
}

SVector2 fNormalize(const SVector2 &a) {
	Scalar len = fLength(a);
	if (len == 0.0f) return a;
	SVector2 b(a);
	b *= (static_cast<Scalar>(1) / len);
	return b;
}

SVector2 fFloor(const SVector2 &a) {
	return
			{
					std::floorf(a.x),
					std::floorf(a.y)
			};
}

SVector2 fCeil(const SVector2 &a) {
	return
			{
					std::ceil(a.x),
					std::ceil(a.y)
			};
}

Scalar fMagnitude(const SVector2 &a) {
	return std::sqrt(fDot(a, a));
}

Scalar fRMagnitude(const SVector2 &a) {
	return rsqrt(fDot(a, a));
}

std::ostream& operator<<(std::ostream &os, const SVector2 &v) {
	return os << "(" << v.x << ", " << v.y << ")";
}

VISRCEND
