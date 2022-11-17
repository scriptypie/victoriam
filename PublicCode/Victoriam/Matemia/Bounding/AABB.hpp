//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_AABB_HPP
#define VICTORIAM_AABB_HPP

#include <Victoriam/Matemia/Bounding/Volume.hpp>

VISRCBEG

struct VIDECL SAABB : public SVolume{
	SPoint3D min;
	SPoint3D max;

	VIDECL inline ~SAABB() = default;
	VIDECL inline  SAABB() = default;
	VIDECL inline  SAABB(const SPoint3D& min, const SPoint3D& max) : min(min), max(max) {}
	VIDECL inline  SAABB(const SAABB&) = default;
	VIDECL inline  SAABB(SAABB&) noexcept = default;

	VIDECL VIREQOUT Bool IsIntersects(const SPoint3D& other) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SAABB   & other) const override;
	VIDECL VIREQOUT Bool IsIntersects(const SSphere & other) const override;

	VIDECL VIREQOUT SPoint3D GetCenter() const;

};

VISRCEND

#endif //VICTORIAM_AABB_HPP
