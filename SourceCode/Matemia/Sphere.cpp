//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/Sphere.hpp>
#include <Victoriam/Matemia/Bounding/AABB.hpp>
#include <Victoriam/Matemia/MPlane.hpp>
#include <Victoriam/World/Components/ComponentTransform.hpp>

VISRCBEG

Bool SSphere::IsIntersects(const SPoint3D &point) const {
	return FDistance(position, point) < radius;
}

Bool SSphere::IsIntersects(const SSphere &sphere) const {
	return FDistance(position, sphere.position) < (radius + sphere.radius);
}

Bool SSphere::IsIntersects(const SAABB &box) const {
	return FDistance(position, box.center) < radius;
}

Bool SSphere::IsOnOrForwardPlane(const SPlane &plan) const {
	return -FDistance(plan, position) < radius;
}

Bool SSphere::IsOnFrustum(const SFrustum &frustum, const SMatrix4 &transform) const {
	const SVector3 globalScale = { FLength(transform[0]), FLength(transform[1]), FLength(transform[2]) };
	const SVector3 globalCenter = (transform * SVector4(position, 1.0F)).xyz;
	const ScalarType maxScale = FMax(FMax(globalScale.x, globalScale.y), globalScale.z);
	SSphere globalSphere(globalCenter, radius * (maxScale * 0.5F));
	return (globalSphere.IsOnOrForwardPlane(frustum.left) &&
	        globalSphere.IsOnOrForwardPlane(frustum.right) &&
	        globalSphere.IsOnOrForwardPlane(frustum.far) &&
	        globalSphere.IsOnOrForwardPlane(frustum.near) &&
	        globalSphere.IsOnOrForwardPlane(frustum.top) &&
	        globalSphere.IsOnOrForwardPlane(frustum.bottom));
}

VISRCEND
