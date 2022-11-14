//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/AABB.hpp>

VISRCBEG

Bool CAABB::IsIntersects(const SPoint3D &other) const {
	return other.x >= m_Min.x &&
	       other.x <= m_Max.x &&
	       other.y >= m_Min.y &&
	       other.y <= m_Max.y &&
	       other.z >= m_Min.z &&
	       other.z <= m_Max.z;
}

Bool CAABB::IsIntersects(const CAABB &other) const {
	return m_Min.x <= other.m_Max.x &&
	       m_Max.x >= other.m_Min.x &&
	       m_Min.y <= other.m_Max.y &&
	       m_Max.y >= other.m_Min.y &&
	       m_Min.z <= other.m_Max.z &&
	       m_Max.z >= other.m_Min.z;
}

SPoint3D CAABB::GetMin() const {
	return m_Min;
}

SPoint3D CAABB::GetCenter() const {
	return m_Center;
}

SPoint3D CAABB::GetMax() const {
	return m_Max;
}

VISRCEND
