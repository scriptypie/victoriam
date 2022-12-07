//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_SCALAR_HPP
#define VICTORIAM_SCALAR_HPP

#include <Victoriam/Core/CNumerics.hpp>
#include <Victoriam/Core/CUtils.hpp>

VISRCBEG

#if __APPLE__ && __ARM_ARCH // Apple's M1 GPU doesn't support full-precise floating point values. :(
VIDECL typedef Float32 ScalarType;
#else
VIDECL typedef Float64 ScalarType; // In other situations Engine will preffer to use full-precise floats.
#endif

template<UInt32 N>
struct VIDECL ScalarArray {
	ScalarType data[N] = {};

	VIDECL inline                              ~ScalarArray() = default;
	VIDECL inline			                    ScalarArray() : data() {}
	VIDECL inline                               ScalarArray(const ScalarArray& other) { for (UInt32 e = 0; e < N; e += 1) data[e] = other[e]; }
	template<UInt32 M> VIDECL inline explicit   ScalarArray(const ScalarArray<M>& other) { for (UInt32 e = 0; e < N; e += 1) data[e] = other[e]; }
	VIDECL inline                               ScalarArray(ScalarArray&& other)  noexcept { for (UInt32 e = 0; e < N; e += 1) data[e] = FMove(other[e]); }
	template<UInt32 M> VIDECL inline explicit   ScalarArray(ScalarArray<M>&& other)  noexcept { for (UInt32 e = 0; e < N; e += 1) data[e] = FMove(other[e]); }
	VIDECL explicit inline                      ScalarArray(ScalarType* arr) { for (UInt32 e = 0; e < N; e += 1) data[e] = FMove(arr[e]); }
	template<class...Args> VIDECL inline        ScalarArray(Args&&...args) : data{FForward<Args>(args)...} {}

	VIDECL inline ScalarType&               operator[](int pos) { return data[pos]; }
	VIDECL inline ScalarType                operator[](int pos) const { return data[pos]; }

};

namespace CONSTANT {

	VIDECL const ScalarType E = CCast<ScalarType>(2.71828182845904523536028747135266250);
	VIDECL const ScalarType DEG = CCast<ScalarType>(57.295779513082320876798154814105);
	VIDECL const ScalarType RAD = CCast<ScalarType>(0.01745329251994329576923690768489);
	VIDECL const ScalarType LOG2E = CCast<ScalarType>(1.44269504088896340735992468100189214);
	VIDECL const ScalarType LOG10E = CCast<ScalarType>(0.434294481903251827651128918916605082);
	VIDECL const ScalarType LN2 = CCast<ScalarType>(0.693147180559945309417232121458176568);
	VIDECL const ScalarType LN10 = CCast<ScalarType>(2.30258509299404568401799145468436421);
	VIDECL const ScalarType PI = CCast<ScalarType>(3.14159265358979323846264338327950288);
	VIDECL const ScalarType PI_HALF = CCast<ScalarType>(1.57079632679489661923132169163975144);
	VIDECL const ScalarType PI_QUAT = CCast<ScalarType>(0.785398163397448309615660845819875721);
	VIDECL const ScalarType ONE_OVER_PI = CCast<ScalarType>(0.318309886183790671537767526745028724);
	VIDECL const ScalarType TWO_OVER_PI = CCast<ScalarType>(0.636619772367581343075535053490057448);
	VIDECL const ScalarType TWO_OVER_SQRT_PI = CCast<ScalarType>(1.12837916709551257389615890312154517);
	VIDECL const ScalarType SQRT2 = CCast<ScalarType>(1.41421356237309504880168872420969808);
	VIDECL const ScalarType SQRT1_2 = CCast<ScalarType>(0.707106781186547524400844362104849039);
	VIDECL const ScalarType INF = CCast<ScalarType>(1e30);
	VIDECL const ScalarType EPSILON = CCast<ScalarType>(1.192092896e-07);

}

VIDECL VIREQOUT ScalarType FSin(const ScalarType& x);   /*  */
VIDECL VIREQOUT ScalarType FCos(const ScalarType& x);   /*  */
VIDECL VIREQOUT ScalarType FTan(const ScalarType& x);   /*  */
VIDECL VIREQOUT ScalarType FArcSin(const ScalarType& x);/*  */
VIDECL VIREQOUT ScalarType FArcCos(const ScalarType& x);/*  */
VIDECL VIREQOUT ScalarType FArcTan(const ScalarType& x);/*  */
VIDECL VIREQOUT ScalarType FSqrt(const ScalarType& x);  /*  */
VIDECL VIREQOUT ScalarType FRSqrt(const ScalarType& x); /*  */
VIDECL VIREQOUT ScalarType FAbs(const ScalarType& x);   /*  */
VIDECL VIREQOUT ScalarType FPow(const ScalarType& x, const ScalarType& y);   /*  */

VIDECL VIREQOUT inline Bool CompareScalar(const ScalarType& a, const ScalarType& b) {
	if (FAbs(a - b) > CONSTANT::EPSILON) return false;
	return true;
}

template<class T>
VIDECL VIREQOUT inline T FRadians(const T& radians) {
	return CCast<T>(CCast<ScalarType>(radians) * CONSTANT::RAD);
}

VIDECL inline void FHashCombine(size_t& seed, size_t hash) {
	hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
	seed ^= hash;
}

template<class T>
VIDECL VIREQOUT inline T FDegrees(const T& radians) {
	return CCast<T>(CCast<ScalarType>(radians) * CONSTANT::DEG);
}

template<class T>
VIDECL VIREQOUT inline Bool IsPowOfTwo(const T& value) {
	return (value != CCast<T>(0)) && ((value & (value - CCast<T>(1))) == CCast<T>(0));
}

VISRCEND

#endif //VICTORIAM_SCALAR_HPP
