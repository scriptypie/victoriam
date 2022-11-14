//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_AABB_HPP
#define VICTORIAM_AABB_HPP

#include <Victoriam/Matemia/MPoint.hpp>

VISRCBEG

class VIDECL CAABB {
	SPoint3D m_Min;
	SPoint3D m_Max;
	SPoint3D m_Center;
public:
	VIDECL inline ~CAABB() = default;
	VIDECL inline  CAABB() = default;
	VIDECL inline  CAABB(const SPoint3D& min, const SPoint3D& max) : m_Min(min), m_Max(max), m_Center((m_Min.x + m_Max.x) / 2.0F, (m_Min.y + m_Max.y) / 2.0F, (m_Min.z + m_Max.z) / 2.0F) {}
	VIDECL inline  CAABB(const SPoint3D& min, const SPoint3D& max, const SPoint3D& center) : m_Min(min), m_Max(max), m_Center(center) {}
	VIDECL inline  CAABB(const CAABB&) = default;
	VIDECL inline  CAABB(CAABB&) noexcept = default;

	VIDECL VIREQOUT Bool IsIntersects(const SPoint3D& other) const;
	VIDECL VIREQOUT Bool IsIntersects(const CAABB   & other) const;

	VIDECL VIREQOUT SPoint3D GetMin() const;
	VIDECL VIREQOUT SPoint3D GetCenter() const;
	VIDECL VIREQOUT SPoint3D GetMax() const;

};

VISRCEND

#endif //VICTORIAM_AABB_HPP
