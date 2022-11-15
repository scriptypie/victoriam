//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/Sphere.hpp>
#include <Victoriam/Matemia/Bounding/AABB.hpp>

VISRCBEG

Bool SSphere::IsIntersects(const SPoint3D &point) const {
	const ScalarType distance = FDistance(position, point);
	return distance < radius;
}

Bool SSphere::IsIntersects(const SSphere &sphere) const {
	const ScalarType distance = FDistance(position, sphere.position);
	return distance < (radius + sphere.radius);
}

Bool SSphere::IsIntersects(const SAABB &box) const {
	const ScalarType x = FMax(box.min.x, FMin(position.x, box.max.x));
	const ScalarType y = FMax(box.min.y, FMin(position.y, box.max.y));
	const ScalarType z = FMax(box.min.z, FMin(position.z, box.max.z));
	const ScalarType distance = FDistance(position, {x, y, z});
	return distance < radius;
}

VISRCEND
