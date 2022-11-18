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

Bool SAABB::IsOnOrForwardPlan(const SPlane &plan) const {
	const ScalarType r = extent.x * FAbs(plan.normal.x) + extent.y * FAbs(plan.normal.y) + extent.z * FAbs(plan.normal.z);
	return -r <= FDistance(plan, center);
}

Bool SAABB::IsOnFrustum(const SFrustum &frustum, const SMatrix4 &transform) const {
	const SVector3 globalCenter = (transform * SVector4(center, 1.0F)).xyz;
	const SVector3 right = (transform[0] * extent.x).xyz;
	const SVector3 up = (transform[1] * extent.y).xyz;
	const SVector3 forward = (-transform[2] * extent.z).xyz;
	const ScalarType newiI = FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), right)) + FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), up)) + FAbs(FDot(SVector3(1.0F, 0.0F, 0.0F), forward));
	const ScalarType newiJ = FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), right)) + FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), up)) + FAbs(FDot(SVector3(0.0F, 1.0F, 0.0F), forward));
	const ScalarType newiK = FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), right)) + FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), up)) + FAbs(FDot(SVector3(0.0F, 0.0F, 1.0F), forward));
	const SAABB globalAABB(globalCenter, newiI, newiJ, newiK);
	return
	globalAABB.IsOnOrForwardPlan(frustum.left) &&
	globalAABB.IsOnOrForwardPlan(frustum.right) &&
	globalAABB.IsOnOrForwardPlan(frustum.top) &&
	globalAABB.IsOnOrForwardPlan(frustum.bottom) &&
	globalAABB.IsOnOrForwardPlan(frustum.far) &&
	globalAABB.IsOnOrForwardPlan(frustum.near);
}

Bool SAABB::IsIntersects(const SAABB &box) const {
	const Bool x = center.x + extent.x >= box.center.x && box.center.x + box.extent.x >= center.x;
	const Bool y = center.y + extent.y >= box.center.y && box.center.y + box.extent.y >= center.y;
	const Bool z = center.z + extent.z >= box.center.z && box.center.z + box.extent.z >= center.z;
	return x && y && z;
}

VISRCEND
