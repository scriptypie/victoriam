//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/AABB.hpp>
#include <Victoriam/Matemia/Bounding/Sphere.hpp>

VISRCBEG

Bool SAABB::IsIntersects(const SPoint3D &other) const {
	return other.x >= min.x &&
	       other.x <= max.x &&
	       other.y >= min.y &&
	       other.y <= max.y &&
	       other.z >= min.z &&
	       other.z <= max.z;
}

Bool SAABB::IsIntersects(const SAABB &other) const {
	return min.x <= other.max.x &&
	       max.x >= other.min.x &&
	       min.y <= other.max.y &&
	       max.y >= other.min.y &&
	       min.z <= other.max.z &&
	       max.z >= other.min.z;
}

SPoint3D SAABB::GetCenter() const {
	return {(min.x + max.x) / 2.0F, (min.y + max.y) / 2.0F, (min.z + max.z) / 2.0F};
}

Bool SAABB::IsIntersects(const SSphere &other) const {
	return other.IsIntersects(*this);
}

VISRCEND
