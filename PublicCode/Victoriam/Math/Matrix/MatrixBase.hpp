//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_MATRIXBASE_HPP
#define VICTORIAM_MATRIXBASE_HPP

#include <Victoriam/Math/Common/ScalarArray.hpp>
#include <Victoriam/Math/Vector/VectorBase.hpp>

VISRCBEG

template<auto C, auto R> struct VIDECL SMatrixBase;

template<>
struct VIDECL SMatrixBase<4, 4>
{
	inline static constexpr auto NUMCOLS = 4 ;
	inline static constexpr auto NUMROWS = 4 ;
	inline static constexpr auto NUMELMS = 16;

	union
	{
		VIDECL Scalar m[NUMROWS][NUMCOLS] = {};
		VIDECL SScalarArray<NUMELMS> data;
	};

	inline SMatrixBase()
	{
		for (auto i = 0; i < min(NUMROWS, NUMCOLS); i++)
			m[i][i] = 1;
	}

	VIDECL inline SMatrixBase(
			const Scalar& m00, const Scalar& m01, const Scalar& m02, const Scalar& m03,
			const Scalar& m10, const Scalar& m11, const Scalar& m12, const Scalar& m13,
			const Scalar& m20, const Scalar& m21, const Scalar& m22, const Scalar& m23,
			const Scalar& m30, const Scalar& m31, const Scalar& m32, const Scalar& m33
	)
	{
		m[0][0] = m00; m[1][0] = m10; m[2][0] = m20; m[3][0] = m30;
		m[0][1] = m01; m[1][1] = m11; m[2][1] = m21; m[3][1] = m31;
		m[0][2] = m02; m[1][2] = m12; m[2][2] = m22; m[3][2] = m32;
		m[0][3] = m03; m[1][3] = m13; m[2][3] = m23; m[3][3] = m33;
	}

};

VISRCEND

#endif //VICTORIAM_MATRIXBASE_HPP
