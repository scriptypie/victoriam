//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#include <Victoriam/Math/Common/Comparator.hpp>

#include <Victoriam/Math/Vector/FuncVector2.hpp>

Vi::Bool Vi::operator==(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					Vi::cComparator::Equal(a.data[0], b.data[0]) &&
					Vi::cComparator::Equal(a.data[1], b.data[1])
			);
}

Vi::Bool Vi::operator!=(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					!Vi::cComparator::Equal(a.data[0], b.data[0]) ||
					!Vi::cComparator::Equal(a.data[1], b.data[1])
			);
}

Vi::Bool Vi::operator<=(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					a.data[0] < b.data[0] &&
					a.data[1] <= b.data[1]
			);
}

Vi::Bool Vi::operator>=(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					a.data[0] >= b.data[0] &&
					a.data[1] >= b.data[1]
			);
}

Vi::Bool Vi::operator<(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					Vi::cComparator::Less(a.data[0], b.data[0]) &&
					Vi::cComparator::Less(a.data[1], b.data[1])
			);
}

Vi::Bool Vi::operator>(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return
			(
					Vi::cComparator::Greater(a.data[0], b.data[0]) &&
					Vi::cComparator::Greater(a.data[1], b.data[1])
			);
}

Vi::sVector2 Vi::max(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return (a > b) ? a : b;
}

Vi::sVector2 Vi::min(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return (a < b) ? a : b;
}

Vi::Scalar Vi::fDot(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return a.x * b.x + a.y * b.y;
}

Vi::Scalar Vi::fSkew(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return Vi::fCross(a, b);
}

Vi::Scalar Vi::fCross(const Vi::sVector2 &a, const Vi::sVector2 &b) {
	return a.x * b.y - a.y * b.x;
}

Vi::Scalar Vi::fLength(const Vi::sVector2 &a) {
	return
			(
					std::sqrtf(
							a.data[0] * a.data[0] +
							a.data[1] * a.data[1]
					)
			);
}

Vi::Scalar Vi::fLength2(const Vi::sVector2 &a) {
	return Vi::fLength(a) * Vi::fLength(a);
}

Vi::Scalar Vi::fDistance(const Vi::sVector2 &from, const Vi::sVector2 &to) {
	return Vi::fLength(
			{
	                   to.data[0] - from.data[0],
	                   to.data[1] - from.data[1]
               });
}

Vi::sVector2 Vi::fNormalize(const Vi::sVector2 &a) {
	Scalar len = fLength(a);
	if (!len) return a;
	sVector2 b(a);
	b *= (static_cast<Scalar>(1) / len);
	return b;
}

Vi::sVector2 Vi::fFloor(const Vi::sVector2 &a) {
	return
			{
					std::floorf(a.x),
					std::floorf(a.y)
			};
}

Vi::sVector2 Vi::fCeil(const Vi::sVector2 &a) {
	return
			{
					std::ceil(a.x),
					std::ceil(a.y)
			};
}

Vi::Scalar Vi::fMagnitude(const Vi::sVector2 &a) {
	return std::sqrt(fDot(a, a));
}

Vi::Scalar Vi::fRMagnitude(const Vi::sVector2 &a) {
	return Vi::rsqrt(fDot(a, a));
}

std::ostream &Vi::operator<<(std::ostream &os, const Vi::sVector2 &v) {
	return os << "(" << v.x << ", " << v.y << ")";
}
