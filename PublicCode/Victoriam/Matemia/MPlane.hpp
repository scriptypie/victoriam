//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MPLANE_HPP
#define VICTORIAM_MPLANE_HPP

#include <Victoriam/Matemia/MVector4.hpp>

VISRCBEG

enum class ECHalfspace { Negative = -1, OnPlane, Positive };

struct VIDECL SPlane {
	union {
		ScalarArray<4> data = {};
		struct {
			ScalarType a, b, c, d;
		};
	};

	VIDECL inline ~SPlane() = default;
	VIDECL inline  SPlane() = default;
	VIDECL inline  SPlane(const SPlane& other) : data(other.a, other.b, other.c, other.d) {}
	VIDECL inline  SPlane(SPlane&& other) noexcept : data(FMove(other.a), FMove(other.b), FMove(other.c), FMove(other.d)) {}
	VIDECL inline  SPlane& operator=(const SPlane& other) noexcept { a = other.a; b = other.b; c = other.c; d = other.d; return *this; }
	VIDECL inline  SPlane& operator=(SPlane&& other) noexcept { a = FMove(other.a); b = FMove(other.b); c = FMove(other.c); d = FMove(other.d); return *this; }
	VIDECL inline  SPlane(const ScalarArray<4>& other) : data(other) {}
	VIDECL inline  SPlane(const ScalarType& _a, const ScalarType& _b, const ScalarType& _c, const ScalarType& _d) : data(_a, _b, _c, _d) {}
	VIDECL inline  SPlane(const SVector2& ab, const SVector2& cd) : data(ab.x, ab.y, cd.x, cd.y) {}
	VIDECL inline  SPlane(const SVector3& abc, const ScalarType& d) : data(abc.x, abc.y, abc.z, d) {}
	VIDECL inline  SPlane(const ScalarType& a, const SVector3& bcd) : data(a, bcd.x, bcd.y, bcd.z) {}

	VIDECL VIREQOUT inline ScalarType& operator[](int pos)       { return data[pos]; }
	VIDECL VIREQOUT inline ScalarType  operator[](int pos) const { return data[pos]; }

};

VISRCEND

#endif //VICTORIAM_MPLANE_HPP
