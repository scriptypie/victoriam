//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_SCALARARRAY_HPP
#define VICTORIAM_SCALARARRAY_HPP

#include <Victoriam/Math/Common/Scalar.hpp>

VISRCBEG

template<UInt16 SIZE>
struct sScalarArray
{
	Scalar data[SIZE] = {};

	VIDECL inline sScalarArray() = default;
	VIDECL inline sScalarArray(sScalarArray&&) noexcept = default;
	VIDECL inline sScalarArray(const sScalarArray&) = default;
	VIDECL inline sScalarArray& operator=(sScalarArray&&) noexcept = default;
	VIDECL inline sScalarArray& operator=(const sScalarArray&) = default;
	VIDECL inline ~sScalarArray() = default;
	VIDECL inline explicit sScalarArray(const Scalar _data[SIZE]) : data(_data) {}

	Scalar& operator[](UInt16 n) { return data[n]; }
	const Scalar& operator[](UInt16 n) const { return data[n]; }

};

VISRCEND

#endif //VICTORIAM_SCALARARRAY_HPP
