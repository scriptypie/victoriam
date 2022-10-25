//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/Math/Matrix/TypeMatrix4.hpp>

VISRCBEG

SMatrix4::SMatrix4
		(
				const Scalar& m00, const Scalar& m01, const Scalar& m02, const Scalar& m03,
				const Scalar& m10, const Scalar& m11, const Scalar& m12, const Scalar& m13,
				const Scalar& m20, const Scalar& m21, const Scalar& m22, const Scalar& m23,
				const Scalar& m30, const Scalar& m31, const Scalar& m32, const Scalar& m33
		) : SMatrixBase(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33)
{}

SMatrix4& SMatrix4::operator+=(const Scalar& s)
{
	for (auto i = 0; i < NUMELMS; i++) data[i] += s;
	return *this;
}
SMatrix4& SMatrix4::operator-=(const Scalar& s)
{
	for (auto i = 0; i < NUMELMS; i++) data[i] -= s;
	return *this;
}
SMatrix4& SMatrix4::operator*=(const Scalar& s)
{
	for (auto i = 0; i < NUMELMS; i++) data[i] *= s;
	return *this;
}
SMatrix4& SMatrix4::operator/=(const Scalar& s)
{
	for (auto i = 0; i < NUMELMS; i++) data[i] /= s;
	return *this;
}

SMatrix4 SMatrix4::operator*(const SMatrix4 &m)
{
	SMatrix4 result = *this;
	for (auto i = 0; i < NUMELMS; i++) result.data[i] *= m.data[i];
	return result;
}

VISRCEND
