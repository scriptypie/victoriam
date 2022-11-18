//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MPLANE_HPP
#define VICTORIAM_MPLANE_HPP

#include <Victoriam/Matemia/MVector3.hpp>

VISRCBEG

struct VIDECL SPlane {
	SVector3 normal = { 0.0F, 1.0F, 0.0F };
	ScalarType distance = {};

	VIDECL inline ~SPlane() = default;
	VIDECL inline  SPlane() = default;
	VIDECL inline  SPlane(const SVector3& p1, const SVector3& norm) : normal(FNormalize(norm)), distance(FDot(normal, p1)) {}

};

VIDECL VIREQOUT inline ScalarType FDistance(const SPlane& plane, const SPoint3D& point) { return FDot(plane.normal, point) - plane.distance; }

VISRCEND

#endif //VICTORIAM_MPLANE_HPP
