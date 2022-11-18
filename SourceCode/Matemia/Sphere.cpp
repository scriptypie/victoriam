//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/Sphere.hpp>
#include <Victoriam/Matemia/Bounding/AABB.hpp>
#include <Victoriam/Matemia/MPlane.hpp>
#include <Victoriam/World/Components/ComponentTransform.hpp>

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
	const ScalarType distance = FDistance(position, box.center);
	return distance < radius;
}

Bool SSphere::IsOnOrForwardPlan(const SPlane &plan) const {
	return FDistance(plan, position) > -radius;
}

Bool SSphere::IsOnFrustum(const SFrustum &frustum, const SMatrix4 &transform) const {
	const SVector3 globalScale = { FLength(transform[0]), FLength(transform[1]), FLength(transform[2]) };
	const SVector3 globalCenter = (transform * SVector4(position, 1.0F)).xyz;
	const ScalarType maxScale = FMax(FMax(globalScale.x, globalScale.y), globalScale.z);
	SSphere globalSphere(globalCenter, radius * (maxScale * 0.5F));
	return (globalSphere.IsOnOrForwardPlan(frustum.left) &&
		globalSphere.IsOnOrForwardPlan(frustum.right) &&
		globalSphere.IsOnOrForwardPlan(frustum.far) &&
		globalSphere.IsOnOrForwardPlan(frustum.near) &&
		globalSphere.IsOnOrForwardPlan(frustum.top) &&
		globalSphere.IsOnOrForwardPlan(frustum.bottom));
}

VISRCEND
