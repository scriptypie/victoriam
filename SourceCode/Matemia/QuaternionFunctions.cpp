//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#include <Victoriam/Matemia/MQuaternion.hpp>

VISRCBEG

SMatrix4 FMatrix4(const SQuaternion& q) {
	SMatrix4 Result(1.0F);
	ScalarType qxx(q.x * q.x);
	ScalarType qyy(q.y * q.y);
	ScalarType qzz(q.z * q.z);
	ScalarType qxz(q.x * q.z);
	ScalarType qxy(q.x * q.y);
	ScalarType qyz(q.y * q.z);
	ScalarType qwx(q.w * q.x);
	ScalarType qwy(q.w * q.y);
	ScalarType qwz(q.w * q.z);

	Result[0][0] = 1.0F - 2.0F * (qyy +  qzz);
	Result[0][1] = 2.0F * (qxy + qwz);
	Result[0][2] = 2.0F * (qxz - qwy);

	Result[1][0] = 2.0F * (qxy - qwz);
	Result[1][1] = 1.0F - 2.0F * (qxx +  qzz);
	Result[1][2] = 2.0F * (qyz + qwx);

	Result[2][0] = 2.0F * (qxz + qwy);
	Result[2][1] = 2.0F * (qyz - qwx);
	Result[2][2] = 1.0F - 2.0F * (qxx +  qyy);

	return Result;
}

ScalarType FDot(const SQuaternion& a, const SQuaternion& b) {
	SVector4 a_tmp(a.x, a.y, a.z, a.w);
	SVector4 b_tmp(b.x, b.y, b.z, b.w);
	return FDot(a_tmp, b_tmp);
}

SQuaternion FCross(const SQuaternion& a, const SQuaternion& b) {
	return { a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z, a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z, a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x };
}

ScalarType FLength(const SQuaternion& quat) {
	return FSqrt(FDot(quat, quat));
}

SQuaternion FNormalize(const SQuaternion& q) {
	ScalarType len = FLength(q);
	if (len <= 0.0F) return { 1.0F, 0.0F, 0.0F, 0.0F };
	ScalarType ool = 1.0F / len;
	return { q.w * ool, q.x * ool, q.y * ool, q.z * ool };
}

VISRCEND
