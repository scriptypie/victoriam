//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#include <Victoriam/Matemia/Bounding/AABB.hpp>
#include <Victoriam/Matemia/Bounding/Sphere.hpp>
#include <Victoriam/Matemia/MMatrix4.hpp>

VISRCBEG

Bool SAABB::IsIntersects(const SPoint3D &other) const {
	SVector3 min = (center - extent) * 0.5F;
	SVector3 max = (center + extent) * 0.5F;
	return other.x >= min.x &&
	       other.x <= max.x &&
	       other.y >= min.y &&
	       other.y <= max.y &&
	       other.z >= min.z &&
	       other.z <= max.z;
}

SPoint3D SAABB::GetCenter() const {
	return center;
}

Bool SAABB::IsIntersects(const SSphere &other) const {
	return other.IsIntersects(*this);
}

Bool SAABB::IsOnOrForwardPlane(const SPlane &plan) const {
	const ScalarType r = extent.x * FAbs(plan.normal.x) + extent.y * FAbs(plan.normal.y) + extent.z * FAbs(plan.normal.z);
	return -r <= FDistance(plan, center);
}

Bool SAABB::IsOnFrustum(const SFrustum &frustum, const SMatrix4 &transform) const {
	const SVector3 globalCenter = (transform * SVector4(center, 1.0F)).xyzw;
	const SVector3 right = SVector4(transform[0] * extent.x).xyzw;
	const SVector3 up = SVector4(transform[1] * extent.y).xyzw;
	const SVector3 forward = SVector4(-transform[2] * extent.z).xyzw;
	const ScalarType x = FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), right)) + FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), up)) + FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), forward));
	const ScalarType y = FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), right)) + FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), up)) + FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), forward));
	const ScalarType z = FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), right)) + FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), up)) + FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), forward));
	const SAABB globalAABB(globalCenter, x, y, z);
	return
			globalAABB.IsOnOrForwardPlane(frustum.left) &&
			globalAABB.IsOnOrForwardPlane(frustum.right) &&
			globalAABB.IsOnOrForwardPlane(frustum.top) &&
			globalAABB.IsOnOrForwardPlane(frustum.bottom) &&
			globalAABB.IsOnOrForwardPlane(frustum.far) &&
			globalAABB.IsOnOrForwardPlane(frustum.near);
}

Bool SAABB::IsIntersects(const SAABB &box) const {
	const Bool x = center.x + extent.x >= box.center.x && box.center.x + box.extent.x >= center.x;
	const Bool y = center.y + extent.y >= box.center.y && box.center.y + box.extent.y >= center.y;
	const Bool z = center.z + extent.z >= box.center.z && box.center.z + box.extent.z >= center.z;
	return x && y && z;
}

VISRCEND
