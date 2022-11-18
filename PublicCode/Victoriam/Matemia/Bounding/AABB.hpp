//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_AABB_HPP
#define VICTORIAM_AABB_HPP

#include <Victoriam/Matemia/Bounding/Volume.hpp>

VISRCBEG

struct VIDECL SAABB : public SVolume{
	SPoint3D center;
	SVector3 extent;

	VIDECL inline ~SAABB() = default;
	VIDECL inline  SAABB() = default;
	VIDECL inline  SAABB(const SPoint3D& min, const SPoint3D& max) : center((max + min) * 0.5F), extent(max.x - center.x, max.y - center.y, max.z - center.z) {}
	VIDECL inline  SAABB(const SPoint3D& _center, const ScalarType& iI, const ScalarType& iJ, const ScalarType& iK) : center(_center), extent(iI, iJ, iK) {}
	VIDECL inline  SAABB(const SAABB&) = default;
	VIDECL inline  SAABB(SAABB&) noexcept = default;

	VIDECL VIREQOUT Bool IsIntersects(const SPoint3D& other) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SSphere & other) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SAABB& box) const override;
	VIDECL VIREQOUT Bool IsOnOrForwardPlan(const SPlane& plan) const override;
	VIDECL VIREQOUT Bool IsOnFrustum(const SFrustum& frustum, const SMatrix4& transform) const override;

	VIDECL VIREQOUT SPoint3D GetCenter() const;

};

VISRCEND

#endif //VICTORIAM_AABB_HPP
