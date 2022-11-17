//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#include <Victoriam/Matemia/Common/Functions.hpp>
#include <Victoriam/Matemia/MPlane.hpp>

VISRCBEG

SPlane FNormalize(const SPlane& plane) {
	ScalarType mag = FSqrt(plane.a * plane.a + plane.b * plane.b + plane.c * plane.c);
	return { plane.a / mag, plane.b / mag, plane.c / mag, plane.d / mag };
}

ScalarType FDistance(const SPlane& plane, const SPoint3D& pt) {
	return plane.a * pt.x + plane.b * pt.y + plane.c * pt.z + plane.d;
}

ECHalfspace FClassifyPoint(const SPlane& plane, const SPoint3D& pt) {
	ScalarType dist = plane.a * pt.x + plane.b * pt.y + plane.c * pt.z + plane.d;
	return dist < 0 ? ECHalfspace::Negative : dist > 0 ? ECHalfspace::Positive : ECHalfspace::OnPlane;
}

VISRCEND
