//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MPLAN_HPP
#define VICTORIAM_MPLAN_HPP

#include <Victoriam/Matemia/MVector3.hpp>

VISRCBEG

struct VIDECL SPlan {
	SVector3 normal = { 0.0F, 1.0F, 0.0F };
	ScalarType distance = {};

	VIDECL inline ~SPlan() = default;
	VIDECL inline  SPlan() = default;
	VIDECL inline  SPlan(const SVector3& p1, const SVector3& norm) : normal(FNormalize(norm)), distance(FDot(normal, p1)) {}

};

VIDECL VIREQOUT inline ScalarType FDistance(const SPlan& plan, const SPoint3D& point) { return FDot(plan.normal, point) - plan.distance; }

VISRCEND

#endif //VICTORIAM_MPLAN_HPP
