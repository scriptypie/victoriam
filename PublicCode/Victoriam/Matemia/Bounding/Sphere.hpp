//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_SPHERE_HPP
#define VICTORIAM_SPHERE_HPP

#include <Victoriam/Matemia/Bounding/Volume.hpp>

VISRCBEG

struct VIDECL SSphere : SVolume {
	SPoint3D position;
	Float32 radius;

	VIDECL inline ~SSphere() = default;
	VIDECL inline  SSphere() = default;
	VIDECL inline  SSphere(const SPoint3D& position, const Float32& rad) : position(position), radius(rad) {}

	VIDECL VIREQOUT Bool IsIntersects(const SPoint3D& point) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SSphere& sphere) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SAABB& box) const override;
	VIDECL VIREQOUT Bool IsOnOrForwardPlan(const SPlane& plan) const override;
	VIDECL VIREQOUT Bool IsOnFrustum(const SFrustum& frustum, const SMatrix4& transform) const override;

};

VISRCEND

#endif //VICTORIAM_SPHERE_HPP
