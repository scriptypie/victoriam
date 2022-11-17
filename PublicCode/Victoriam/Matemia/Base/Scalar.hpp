//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_SCALAR_HPP
#define VICTORIAM_SCALAR_HPP

#include <Victoriam/Core/CNumerics.hpp>
#include <Victoriam/Core/CUtils.hpp>
#include <utility>

VISRCBEG

VIDECL typedef Float32 ScalarType;

template<UInt32 N>
struct VIDECL ScalarArray {
	ScalarType data[N] = {};

	VIDECL inline                              ~ScalarArray() = default;
	VIDECL inline			                    ScalarArray() : data() {}
	VIDECL inline                               ScalarArray(const ScalarArray& other) { for (UInt32 e = 0; e < N; e += 1) data[e] = other[e]; }
	template<UInt32 M> VIDECL inline explicit   ScalarArray(const ScalarArray<M>& other) { for (UInt32 e = 0; e < M; e += 1) data[e] = other[e]; }
	VIDECL inline                               ScalarArray(ScalarArray&& other)  noexcept { for (UInt32 e = 0; e < N; e += 1) data[e] = FMove(other[e]); }
	template<UInt32 M> VIDECL inline explicit   ScalarArray(ScalarArray<M>&& other)  noexcept { for (UInt32 e = 0; e < M; e += 1) data[e] = FMove(other[e]); }
	VIDECL explicit inline                      ScalarArray(ScalarType* arr) { for (UInt32 e = 0; e < N; e += 1) data[e] = FMove(arr[e]); }
	template<class...Args> VIDECL inline        ScalarArray(Args&&...args) : data{std::forward<Args>(args)...} {}

	VIDECL inline ScalarType&               operator[](int pos) { return data[pos]; }
	VIDECL inline ScalarType                operator[](int pos) const { return data[pos]; }

};

namespace Constant {

	VIDECL constexpr ScalarType E = 2.71828182845904523536028747135266250F;   /* e              */
	VIDECL constexpr ScalarType LOG2E = 1.44269504088896340735992468100189214F;   /* log2(e)        */
	VIDECL constexpr ScalarType LOG10E = 0.434294481903251827651128918916605082F;  /* log10(e)       */
	VIDECL constexpr ScalarType LN2 = 0.693147180559945309417232121458176568F;  /* loge(2)        */
	VIDECL constexpr ScalarType LN10 = 2.30258509299404568401799145468436421F;   /* loge(10)       */
	VIDECL constexpr ScalarType PI = 3.14159265358979323846264338327950288F;   /* pi             */
	VIDECL constexpr ScalarType PI_HALF = 1.57079632679489661923132169163975144F;   /* pi/2           */
	VIDECL constexpr ScalarType PI_QUAT = 0.785398163397448309615660845819875721F;  /* pi/4           */
	VIDECL constexpr ScalarType ONE_OVER_PI = 0.318309886183790671537767526745028724F;  /* 1/pi           */
	VIDECL constexpr ScalarType TWO_OVER_PI = 0.636619772367581343075535053490057448F;  /* 2/pi           */
	VIDECL constexpr ScalarType TWO_OVER_SQRT_PI = 1.12837916709551257389615890312154517F;   /* 2/sqrt(pi)     */
	VIDECL constexpr ScalarType SQRT2 = 1.41421356237309504880168872420969808F;   /* sqrt(2)        */
	VIDECL constexpr ScalarType SQRT1_2 = 0.707106781186547524400844362104849039F;  /* 1/sqrt(2)      */
	VIDECL constexpr ScalarType INF = 1e30F;
	VIDECL constexpr ScalarType EPSILON = 1.192092896e-07F;

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

VIDECL VIREQOUT inline Bool CompareScalar(const ScalarType& a, const ScalarType& b) {
	if (FAbs(a - b) > Constant::EPSILON) return false;
	return true;
}

template<class T>
VIDECL VIREQOUT inline T FRadians(const T& radians) {
	return CCast<T>(CCast<ScalarType>(radians) * CCast<ScalarType>(0.01745329251994329576923690768489F));
}

VIDECL inline void FHashCombine(size_t& seed, size_t hash) {
	hash += 0x9e3779b9 + (seed << 6) + (seed >> 2);
	seed ^= hash;
}

template<class T>
VIDECL VIREQOUT inline T FDegrees(const T& radians) {
	return CCast<T>(CCast<ScalarType>(radians) * CCast<ScalarType>(57.295779513082320876798154814105F));
}

template<class T>
VIDECL VIREQOUT inline Bool IsPowOfTwo(const T& value) {
	return (value != 0) && ((value & (value - 1)) == 0);
}

VISRCEND

#endif //VICTORIAM_SCALAR_HPP
