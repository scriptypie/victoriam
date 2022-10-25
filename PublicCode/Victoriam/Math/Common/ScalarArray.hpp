//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_SCALARARRAY_HPP
#define VICTORIAM_SCALARARRAY_HPP

#include <Victoriam/Math/Common/Scalar.hpp>

VISRCBEG

template<UInt16 SIZE>
struct SScalarArray
{
	Scalar data[SIZE] = {};

	VIDECL inline SScalarArray() = default;
	VIDECL inline SScalarArray(SScalarArray&&) noexcept = default;
	VIDECL inline SScalarArray(const SScalarArray&) = default;
	VIDECL inline SScalarArray& operator=(SScalarArray&&) noexcept = default;
	VIDECL inline SScalarArray& operator=(const SScalarArray&) = default;
	VIDECL inline ~SScalarArray() = default;
	VIDECL inline explicit SScalarArray(const Scalar _data[SIZE]) : data(_data) {}

	Scalar& operator[](UInt16 n) { return data[n]; }
	const Scalar& operator[](UInt16 n) const { return data[n]; }

};

VISRCEND

#endif //VICTORIAM_SCALARARRAY_HPP
