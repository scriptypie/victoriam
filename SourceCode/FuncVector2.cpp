//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#include <Victoriam/Math/Common/Comparator.hpp>

#include <Victoriam/Math/Vector/FuncVector2.hpp>

VISRCBEG

Bool operator==(const SVector2 &a, const SVector2 &b) {
	return
			(
					CComparator::Equal(a.data[0], b.data[0]) &&
					CComparator::Equal(a.data[1], b.data[1])
			);
}

Bool operator!=(const SVector2 &a, const SVector2 &b) {
	return
			(
					!CComparator::Equal(a.data[0], b.data[0]) ||
					!CComparator::Equal(a.data[1], b.data[1])
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
					CComparator::Less(a.data[0], b.data[0]) &&
					CComparator::Less(a.data[1], b.data[1])
			);
}

Bool operator>(const SVector2 &a, const SVector2 &b) {
	return
			(
					CComparator::Greater(a.data[0], b.data[0]) &&
					CComparator::Greater(a.data[1], b.data[1])
			);
}

SVector2 max(const SVector2 &a, const SVector2 &b) {
	return (a > b) ? a : b;
}

SVector2 min(const SVector2 &a, const SVector2 &b) {
	return (a < b) ? a : b;
}

Scalar FDot(const SVector2 &a, const SVector2 &b) {
	return a.x * b.x + a.y * b.y;
}

Scalar FSkew(const SVector2 &a, const SVector2 &b) {
	return FCross(a, b);
}

Scalar FCross(const SVector2 &a, const SVector2 &b) {
	return a.x * b.y - a.y * b.x;
}

Scalar FLength(const SVector2 &a) {
	return
			(
					std::sqrtf(
							a.data[0] * a.data[0] +
							a.data[1] * a.data[1]
					)
			);
}

Scalar FLength2(const SVector2 &a) {
	return FLength(a) * FLength(a);
}

Scalar FDistance(const SVector2 &from, const SVector2 &to) {
	return FLength(
			{
	                   to.data[0] - from.data[0],
	                   to.data[1] - from.data[1]
               });
}

SVector2 FNormalize(const SVector2 &a) {
	Scalar len = FLength(a);
	if (len == 0.0f) return a;
	SVector2 b(a);
	b *= (static_cast<Scalar>(1) / len);
	return b;
}

SVector2 FFloor(const SVector2 &a) {
	return
			{
					std::floorf(a.x),
					std::floorf(a.y)
			};
}

SVector2 FCeil(const SVector2 &a) {
	return
			{
					std::ceil(a.x),
					std::ceil(a.y)
			};
}

Scalar FMagnitude(const SVector2 &a) {
	return std::sqrt(FDot(a, a));
}

Scalar FRMagnitude(const SVector2 &a) {
	return rsqrt(FDot(a, a));
}

std::ostream& operator<<(std::ostream &os, const SVector2 &v) {
	return os << "(" << v.x << ", " << v.y << ")";
}

VISRCEND
