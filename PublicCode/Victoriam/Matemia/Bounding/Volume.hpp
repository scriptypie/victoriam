//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_VOLUME_HPP
#define VICTORIAM_VOLUME_HPP

#include <Victoriam/Matemia/Base/Base.hpp>
#include <Victoriam/Matemia/MPoint.hpp>
#include <Victoriam/Matemia/MFrustum.hpp>

VISRCBEG

struct VIDECL SVolume {
public:
	VIDECL VIREQOUT virtual Bool IsIntersects(const SPoint3D& point) const = 0;
	VIDECL VIREQOUT virtual Bool IsIntersects(const SSphere& sphere) const = 0;
	VIDECL VIREQOUT virtual Bool IsIntersects(const SAABB& box) const = 0;

	VIDECL VIREQOUT virtual Bool IsOnOrForwardPlan(const SPlane& plan) const = 0;
	VIDECL VIREQOUT virtual Bool IsOnFrustum(const SFrustum& frustum, const SMatrix4& transform) const = 0;
	VIDECL VIREQOUT inline Bool IsOnFrustum(const SFrustum& frustum) const {
		return  IsOnOrForwardPlan(frustum.left) &&
				IsOnOrForwardPlan(frustum.right) &&
				IsOnOrForwardPlan(frustum.top) &&
				IsOnOrForwardPlan(frustum.bottom) &&
				IsOnOrForwardPlan(frustum.near) &&
				IsOnOrForwardPlan(frustum.far);
	}
};

VISRCEND

#endif //VICTORIAM_VOLUME_HPP
