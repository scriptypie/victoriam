//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_MVECTOR2_HPP
#define VICTORIAM_MVECTOR2_HPP

#include <Victoriam/Matemia/Base/Scalar.hpp>

VISRCBEG

struct VIDECL SVector2 {
	union {
		ScalarArray<2> data = {};
		struct {
			union {
				ScalarType x, u;
			};
			union {
				ScalarType y, v;
			};
		};
	};

	VIDECL inline static    ScalarArray<2> Zero = { 0.0F,  0.0F };
	VIDECL inline static    ScalarArray<2> One  = { 1.0F,  1.0F };
	VIDECL inline static    ScalarArray<2> Up   = { 1.0F,  0.0F };
	VIDECL inline static    ScalarArray<2> Right= { 0.0F,  1.0F };
	VIDECL inline static    ScalarArray<2> Down = {-1.0F,  0.0F };
	VIDECL inline static    ScalarArray<2> Left=  { 0.0F, -1.0F };

	VIDECL inline          ~SVector2() = default;
	VIDECL inline           SVector2() : data() {}
	VIDECL inline explicit  SVector2(const ScalarArray<2>& other) { for (UInt8 i = 0; i < 2; i+=1) data[i] = other[i]; }
	VIDECL inline explicit  SVector2(const ScalarType& v) : data{v, v} {}
	VIDECL inline           SVector2(const ScalarType& x, const ScalarType& y) : data{x, y} {}
	VIDECL inline           SVector2(const SVector2& other) : x(other.x), y(other.y) {}
	VIDECL inline           SVector2(SVector2&& other) noexcept : x(FMove(other.x)), y(FMove(other.y)) {}
	VIDECL inline           SVector2& operator=(const SVector2& other) { x = other.x; y = other.y; return *this; }
	VIDECL inline           SVector2& operator=(SVector2&& other) noexcept { x = FMove(other.x); y = FMove(other.y); return *this; }

						VIDECL VIREQOUT inline  ScalarType& operator[](int pos) { return data[pos]; }
						VIDECL VIREQOUT inline  ScalarType  operator[](int pos) const { return data[pos]; }
						VIDECL VIREQOUT inline  SVector2 operator+(const SVector2& b) const { return { x + b.x, y + b.y }; }
						VIDECL VIREQOUT inline  SVector2 operator-(const SVector2& b) const { return { x - b.x, y - b.y }; }
						VIDECL VIREQOUT inline  SVector2 operator*(const SVector2& b) const { return { x * b.x, y * b.y }; }
						VIDECL VIREQOUT inline  SVector2 operator/(const SVector2& b) const { return { x / b.x, y / b.y }; }
						VIDECL VIREQOUT inline  SVector2& operator+=(const SVector2& b) { *this = { x + b.x, y + b.y }; return *this; }
						VIDECL VIREQOUT inline  SVector2& operator-=(const SVector2& b) { *this = { x - b.x, y - b.y }; return *this; }
						VIDECL VIREQOUT inline  SVector2& operator*=(const SVector2& b) { *this = { x * b.x, y * b.y }; return *this; }
						VIDECL VIREQOUT inline  SVector2& operator/=(const SVector2& b) { *this = { x / b.x, y / b.y }; return *this; }
	template<class T>   VIDECL VIREQOUT inline  SVector2 operator+(const T& b) const { return { x + b, y + b }; }
	template<class T>   VIDECL VIREQOUT inline  SVector2 operator-(const T& b) const { return { x - b, y - b }; }
	template<class T>   VIDECL VIREQOUT inline  SVector2 operator*(const T& b) const { return { x * b, y * b }; }
	template<class T>   VIDECL VIREQOUT inline  SVector2 operator/(const T& b) const { return { x / b, y / b }; }
	template<class T>   VIDECL VIREQOUT inline  SVector2& operator+=(const T& b) { *this = { x + b, y + b }; return *this; }
	template<class T>   VIDECL VIREQOUT inline  SVector2& operator-=(const T& b) { *this = { x - b, y - b }; return *this; }
	template<class T>   VIDECL VIREQOUT inline  SVector2& operator*=(const T& b) { *this = { x * b, y * b }; return *this; }
	template<class T>   VIDECL VIREQOUT inline  SVector2& operator/=(const T& b) { *this = { x / b, y / b }; return *this; }
	template<class T>   VIDECL VIREQOUT inline Bool      operator==(const T&) const { return false; }
	template<class T>   VIDECL VIREQOUT inline Bool      operator!=(const T&) const { return true; }
	template<>          VIDECL VIREQOUT inline Bool      operator==(const SVector2& other) const { return x == other.x && y == other.y; }
	template<>          VIDECL VIREQOUT inline Bool      operator!=(const SVector2& other) const { return !(*this == other); }
};

VIDECL inline SVector2  FSqrt(const SVector2& v) { return v * v; }
VIDECL inline ScalarType FDot(const SVector2& a, const SVector2& b) { SVector2 tmp = a * b; return tmp.x + tmp.y; }
VIDECL inline ScalarType FLength(const SVector2& a, const SVector2& b) { return FSqrt(FDot(a, b)); }
VIDECL inline ScalarType FDistance(const SVector2& a, const SVector2& b) { auto tmp = b - a; return FLength(tmp, tmp); }
VIDECL inline SVector2   FNormalize(const SVector2& v) { return v * (1.0F / FLength(v, v)); }
VIDECL inline SVector2   FReflect(const SVector2& i, const SVector2& n) { return i - n * FDot(n, i) * 2.0F; }
VIDECL inline SVector2   FRefract(const SVector2& i, const SVector2& n, ScalarType eta) { auto dv(FDot(n, i)); auto k(1.0F - eta * eta * (1.0F - dv * dv)); return { (k >= 0.0F) ? (i * eta - (n * (eta * dv + FSqrt(k)))) : SVector2(0.0F) }; }

VISRCEND

#endif //VICTORIAM_MVECTOR2_HPP
