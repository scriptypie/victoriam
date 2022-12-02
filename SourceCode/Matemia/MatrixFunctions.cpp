//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#include <Victoriam/Matemia/MMatrix4.hpp>

VISRCBEG

SMatrix4 FInverse(const SMatrix4& m) {
	const ScalarType Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
	const ScalarType Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
	const ScalarType Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
	const ScalarType Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	const ScalarType Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	const ScalarType Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
	const ScalarType Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
	const ScalarType Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
	const ScalarType Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
	const ScalarType Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	const ScalarType Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	const ScalarType Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
	const ScalarType Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
	const ScalarType Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
	const ScalarType Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
	const ScalarType Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	const ScalarType Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	const ScalarType Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
	const SVector4   Fac0(Coef00, Coef00, Coef02, Coef03);
	const SVector4   Fac1(Coef04, Coef04, Coef06, Coef07);
	const SVector4   Fac2(Coef08, Coef08, Coef10, Coef11);
	const SVector4   Fac3(Coef12, Coef12, Coef14, Coef15);
	const SVector4   Fac4(Coef16, Coef16, Coef18, Coef19);
	const SVector4   Fac5(Coef20, Coef20, Coef22, Coef23);
	const SVector4   Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
	const SVector4   Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
	const SVector4   Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
	const SVector4   Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
	const SVector4   Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
	const SVector4   Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
	const SVector4   Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
	const SVector4   Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
	const SVector4   SignA(CCast<ScalarType>(1), CCast<ScalarType>(-1), CCast<ScalarType>(1), CCast<ScalarType>(-1));
	const SVector4   SignB(CCast<ScalarType>(-1), CCast<ScalarType>(1), CCast<ScalarType>(-1), CCast<ScalarType>(1));
	const SMatrix4   Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);
	const SVector4   Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);
	const SVector4   Dot0(m[0] * Row0);
	const ScalarType Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);
	const ScalarType OneOverDeterminant = CCast<ScalarType>(1) / Dot1;

	return Inverse * OneOverDeterminant;
}

SMatrix4 FScale(const SMatrix4& m, const SVector3& v) {
	SMatrix4 Result;
	Result[0] = m[0] * v[0];
	Result[1] = m[1] * v[1];
	Result[2] = m[2] * v[2];
	Result[3] = m[3];
	return Result;
}

SMatrix4 FTranslate(const SMatrix4& m, const SVector3& v) {
	SMatrix4 Result(m);
	Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
	return Result;
}

SMatrix4 FRotate(const SMatrix4& m, const SVector3& v, const ScalarType& angle) {
	const ScalarType a = angle;
	const ScalarType c = FCos(a);
	const ScalarType s = FSin(a);

	SVector3 axis(FNormalize(v));
	SVector3 temp((axis * (CCast<ScalarType>(1) - c)));

	SMatrix4 Rotate;
	Rotate[0][0] = c + temp[0] * axis[0];
	Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

	Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	Rotate[1][1] = c + temp[1] * axis[1];
	Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

	Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	Rotate[2][2] = c + temp[2] * axis[2];

	SMatrix4 Result;
	Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
	Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
	Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
	Result[3] = m[3];
	return Result;
}

SMatrix4 FRotateX(const SMatrix4& m, const ScalarType& angle) {
	return FRotate(m, { CCast<ScalarType>(1), 0, 0 }, angle);
}

SMatrix4 FRotateY(const SMatrix4& m, const ScalarType& angle) {
	return FRotate(m, { 0, CCast<ScalarType>(1), 0 }, angle);
}

SMatrix4 FRotateZ(const SMatrix4& m, const ScalarType& angle) {
	return FRotate(m, { 0, 0, CCast<ScalarType>(1) }, angle);
}

SMatrix4 FLookAt(const SVector3& position, const SVector3& direction, const SVector3& up) {
	const SVector3 f(FNormalize(direction - position));
	const SVector3 s(FNormalize(FCross(f, up)));
	const SVector3 u(FCross(s, f));

	SMatrix4 Result(1);
	Result[0][0] = s.x;
	Result[1][0] = s.y;
	Result[2][0] = s.z;
	Result[0][1] = u.x;
	Result[1][1] = u.y;
	Result[2][1] = u.z;
	Result[0][2] =-f.x;
	Result[1][2] =-f.y;
	Result[2][2] =-f.z;
	Result[3][0] =-FDot(s, position);
	Result[3][1] =-FDot(u, position);
	Result[3][2] = FDot(f, position);
	return Result;
}

SMatrix4 FPerspective(const ScalarType& fovy, const ScalarType& aspect, const ScalarType& zNear) {
	const ScalarType range = FTan(fovy / CCast<ScalarType>(2)) * zNear;
	const ScalarType left = -range * aspect;
	const ScalarType right = range * aspect;
	const ScalarType bottom = -range;
	const ScalarType top = range;
	const ScalarType ep = CONSTANT::EPSILON;

	SMatrix4 Result(0.0F);
	Result[0][0] = (CCast<ScalarType>(2) * zNear) / (right - left);
	Result[1][1] = (CCast<ScalarType>(2) * zNear) / (top - bottom);
	Result[2][2] = ep - CCast<ScalarType>(1);
	Result[2][3] = -CCast<ScalarType>(1);
	Result[3][2] = (ep - CCast<ScalarType>(2)) * zNear;
	return Result;
}

SMatrix4 FPerspective(const ScalarType& fovy, const ScalarType& aspect, const ScalarType& zNear, const ScalarType& zFar) {
	const ScalarType tanHalfFovy = FTan(fovy / CCast<ScalarType>(2));

	SMatrix4 Result(0.0F);
	Result[0][0] = CCast<ScalarType>(1) / (aspect * tanHalfFovy);
	Result[1][1] = CCast<ScalarType>(1) / (tanHalfFovy);
	Result[2][2] = - (zFar + zNear) / (zFar - zNear);
	Result[2][3] = -CCast<ScalarType>(1);
	Result[3][2] = - (CCast<ScalarType>(2) * zFar * zNear) / (zFar - zNear);
	return Result;
}

SMatrix4 FOrthographic(const ScalarType& left, const ScalarType& right, const ScalarType& bottom, const ScalarType& top, const ScalarType& zNear, const ScalarType& zFar) {
	SMatrix4 Result(CCast<ScalarType>(1));
	Result[0][0] = CCast<ScalarType>(2) / (right - left);
	Result[1][1] = CCast<ScalarType>(2) / (top - bottom);
	Result[2][2] = - CCast<ScalarType>(2) / (zFar - zNear);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	Result[3][2] = - (zFar + zNear) / (zFar - zNear);
	return Result;
}

SMatrix4 FOrthographic(const SRect& bounds, const ScalarType& zNear, const ScalarType& zFar) {
	return FOrthographic(bounds.left, bounds.right, bounds.bottom, bounds.top, zNear, zFar);
}

VISRCEND
