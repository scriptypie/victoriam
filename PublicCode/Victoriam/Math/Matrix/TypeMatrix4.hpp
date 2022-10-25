//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_TYPEMATRIX4_HPP
#define VICTORIAM_TYPEMATRIX4_HPP

#include <Victoriam/Math/Matrix/MatrixBase.hpp>

VISRCBEG

struct VIDECL SMatrix4 : SMatrixBase<4, 4>
{
	SMatrix4() = default;
	~SMatrix4() = default;

	VIDECL SMatrix4(
			const Scalar& m00, const Scalar& m01, const Scalar& m02, const Scalar& m03,
			const Scalar& m10, const Scalar& m11, const Scalar& m12, const Scalar& m13,
			const Scalar& m20, const Scalar& m21, const Scalar& m22, const Scalar& m23,
			const Scalar& m30, const Scalar& m31, const Scalar& m32, const Scalar& m33
	);

	SMatrix4& operator+=(const Scalar& s);
	SMatrix4& operator-=(const Scalar& s);
	SMatrix4& operator*=(const Scalar& s);
	SMatrix4& operator/=(const Scalar& s);

	SMatrix4  operator*(const SMatrix4& m);

};

VISRCEND

#endif //VICTORIAM_TYPEMATRIX4_HPP
