//
// Created by Вячеслав Кривенко on 09.10.2022.
//

#include <Victoriam/Math/Common/Scalar.hpp>

VISRCBEG

Scalar rsqrt(const Scalar &a) {
	ScalarCaster i = *reinterpret_cast<ScalarCaster*>(&const_cast<Scalar&>(a));
	i = 0x5f3759df - (i >> 1);
	Scalar b = *reinterpret_cast<Scalar*>(&i);
	return b * (1.5f - 0.5f * a * b * b);
}

VISRCEND
