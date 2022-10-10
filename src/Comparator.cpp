//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#include <cmath>
#include <cfloat>

#include <Victoriam/Math/Common/Comparator.hpp>

Vi::Bool Vi::cComparator::Equal(const Vi::Scalar &a, const Vi::Scalar &b) {
	return ::fabsf(a - b) <= FLT_EPSILON;
}

Vi::Bool Vi::cComparator::Greater(const Vi::Scalar &a, const Vi::Scalar &b) {
	Scalar fabs_a = ::fabsf(a);
	Scalar fabs_b = ::fabsf(b);
	return (a - b) > ((fabs_a < fabs_b ? fabs_b : fabs_a) * FLT_EPSILON);
}

Vi::Bool Vi::cComparator::Less(const Vi::Scalar &a, const Vi::Scalar &b) {
	Scalar fabs_a = ::fabsf(a);
	Scalar fabs_b = ::fabsf(b);
	return (b - a) > ((fabs_a < fabs_b ? fabs_b : fabs_a) * FLT_EPSILON);
}
