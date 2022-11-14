//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#include <Victoriam/Matemia/Base/Scalar.hpp>
#include <cmath>

VISRCBEG

ScalarType FSin(const ScalarType& x) {
	return std::sin(x);
}

ScalarType FCos(const ScalarType& x) {
	return std::cos(x);
}

ScalarType FTan(const ScalarType& x) {
	return std::tan(x);
}

ScalarType FArcSin(const ScalarType& x) {
	return std::asin(x);
}

ScalarType FArcCos(const ScalarType& x) {
	return std::acos(x);
}

ScalarType FArcTan(const ScalarType& x) {
	return std::atan(x);
}

ScalarType FSqrt(const ScalarType& x) {
	return std::sqrt(x);
}

ScalarType FRSqrt(const ScalarType& x) {
	union {
		ScalarType  f;
		UInt32      i;
	}
	conv = { .f = x };
	conv.i  = 0x5F3759DF - (conv.i >> 1);
	conv.f *= 1.5F - (x * 0.5F * conv.f * conv.f);
	return conv.f;
}

ScalarType FAbs(const ScalarType& x) {
	return std::abs(x);
}


VISRCEND
