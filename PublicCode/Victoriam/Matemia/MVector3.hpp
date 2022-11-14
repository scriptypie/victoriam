//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MVECTOR3_HPP
#define VICTORIAM_MVECTOR3_HPP

#include <Victoriam/Matemia/MVector2.hpp>

VISRCBEG

struct VIDECL SVector3 {
	union {
		ScalarArray<3> data = {};
		struct {
			union {
				ScalarArray<3> xyz;
				ScalarArray<3> rgb;
				struct {
					union {
						ScalarArray<2> xy;
						ScalarArray<2> uv;
						struct {
							union {
								ScalarType x, u, r;
							};
							union {
								ScalarType y, v, g;
							};
						};
					};
					union {
						ScalarType z, s, b;
					};
				};
			};
		};
	};

	VIDECL inline static    ScalarArray<3> Zero     = { 0.0F, 0.0F, 0.0F };
	VIDECL inline static    ScalarArray<3> One      = { 1.0F, 1.0F, 1.0F };
	VIDECL inline static    ScalarArray<3> Up       = { 0.0F, 1.0F, 0.0F };
	VIDECL inline static    ScalarArray<3> Right    = { 1.0F, 0.0F, 0.0F };
	VIDECL inline static    ScalarArray<3> Down     = { 0.0F,-1.0F, 0.0F };
	VIDECL inline static    ScalarArray<3> Left     = {-1.0F, 0.0F, 0.0F };
	VIDECL inline static    ScalarArray<3> Forward  = { 0.0F, 0.0F, 1.0F };
	VIDECL inline static    ScalarArray<3> Backward = { 0.0F, 0.0F,-1.0F };

	VIDECL inline          ~SVector3() = default;
	VIDECL inline           SVector3() : data() {}
	VIDECL inline explicit  SVector3(const ScalarArray<2>& other) : data(other) { }
	VIDECL inline explicit  SVector3(const ScalarArray<3>& other) : data(other) { }
	VIDECL inline explicit  SVector3(const ScalarType& x) : data(x, x, x) {}
	VIDECL inline           SVector3(const ScalarType& x, const ScalarType& y, const ScalarType& z) : data(x, y, z) {}
	VIDECL inline explicit  SVector3(const SVector2& v) : data(v.x, v.y, 0.0F) {}
	VIDECL inline explicit  SVector3(SVector2&& v) : data(FMove(v.x), FMove(v.y), 0.0F) {}
	VIDECL inline           SVector3(const SVector2& v, const ScalarType& z) : data(v.x, v.y, z) {}
	VIDECL inline           SVector3(const ScalarType& x, const SVector2& v) : data(x, v.x, v.y) {}
	VIDECL inline           SVector3(const SVector3& other) : data(other.data) {}
	VIDECL inline           SVector3& operator=(const SVector3& other) { x = other.x; y = other.y; z = other.z; return *this; }
	VIDECL inline           SVector3& operator=(SVector3&& other) noexcept { x = FMove(other.x); y = FMove(other.y); z = FMove(other.z); return *this; }

						VIDECL VIREQOUT inline ScalarType& operator[](int pos) { return data[pos]; }
						VIDECL VIREQOUT inline ScalarType  operator[](int pos) const { return data[pos]; }

						VIDECL VIREQOUT inline SVector3  operator+ (const SVector3& other) const { return { x + other.x,                  y + other.y,                  z + other.z                                }; }
						VIDECL VIREQOUT inline SVector3  operator- (const SVector3& other) const { return { x - other.x,                  y - other.y,                  z - other.z                                }; }
						VIDECL VIREQOUT inline SVector3  operator* (const SVector3& other) const { return { x * other.x,                  y * other.y,                  z * other.z                                }; }
						VIDECL VIREQOUT inline SVector3  operator/ (const SVector3& other) const { return { x / other.x,                  y / other.y,                  z / other.z                                }; }
						VIDECL VIREQOUT inline SVector3  operator+ (const SVector2& other) const { return { x + other.x,                  y + other.y,                  z                                          }; }
						VIDECL VIREQOUT inline SVector3  operator- (const SVector2& other) const { return { x - other.x,                  y - other.y,                  z                                          }; }
						VIDECL VIREQOUT inline SVector3  operator* (const SVector2& other) const { return { x * other.x,                  y * other.y,                  z                                          }; }
						VIDECL VIREQOUT inline SVector3  operator/ (const SVector2& other) const { return { x / other.x,                  y / other.y,                  z                                          }; }
	template<class T>   VIDECL VIREQOUT inline SVector3  operator+ (const T&        other) const { return { x + CCast<ScalarType>(other), y + CCast<ScalarType>(other), z + CCast<ScalarType>(other)               }; }
	template<class T>   VIDECL VIREQOUT inline SVector3  operator- (const T&        other) const { return { x - CCast<ScalarType>(other), y - CCast<ScalarType>(other), z - CCast<ScalarType>(other)               }; }
	template<class T>   VIDECL VIREQOUT inline SVector3  operator* (const T&        other) const { return { x * CCast<ScalarType>(other), y * CCast<ScalarType>(other), z * CCast<ScalarType>(other)               }; }
	template<class T>   VIDECL VIREQOUT inline SVector3  operator/ (const T&        other) const { return { x / CCast<ScalarType>(other), y / CCast<ScalarType>(other), z / CCast<ScalarType>(other)               }; }
						VIDECL VIREQOUT inline SVector3& operator+=(const SVector3& other)       { *this= { x + other.x,                  y + other.y,                  z + other.z };                  return *this; }
						VIDECL VIREQOUT inline SVector3& operator-=(const SVector3& other)       { *this= { x - other.x,                  y - other.y,                  z - other.z };                  return *this; }
						VIDECL VIREQOUT inline SVector3& operator*=(const SVector3& other)       { *this= { x * other.x,                  y * other.y,                  z * other.z };                  return *this; }
						VIDECL VIREQOUT inline SVector3& operator/=(const SVector3& other)       { *this= { x / other.x,                  y / other.y,                  z / other.z };                  return *this; }
						VIDECL VIREQOUT inline SVector3& operator+=(const SVector2& other)       { *this= { x + other.x,                  y + other.y,                  z };                            return *this; }
						VIDECL VIREQOUT inline SVector3& operator-=(const SVector2& other)       { *this= { x - other.x,                  y - other.y,                  z };                            return *this; }
						VIDECL VIREQOUT inline SVector3& operator*=(const SVector2& other)       { *this= { x * other.x,                  y * other.y,                  z };                            return *this; }
						VIDECL VIREQOUT inline SVector3& operator/=(const SVector2& other)       { *this= { x / other.x,                  y / other.y,                  z };                            return *this; }
	template<class T>   VIDECL VIREQOUT inline SVector3& operator+=(const T&        other)       { *this= { x + CCast<ScalarType>(other), y + CCast<ScalarType>(other), z + CCast<ScalarType>(other) }; return *this; }
	template<class T>   VIDECL VIREQOUT inline SVector3& operator-=(const T&        other)       { *this= { x - CCast<ScalarType>(other), y - CCast<ScalarType>(other), z - CCast<ScalarType>(other) }; return *this; }
	template<class T>   VIDECL VIREQOUT inline SVector3& operator*=(const T&        other)       { *this= { x * CCast<ScalarType>(other), y * CCast<ScalarType>(other), z * CCast<ScalarType>(other) }; return *this; }
	template<class T>   VIDECL VIREQOUT inline SVector3& operator/=(const T&        other)       { *this= { x / CCast<ScalarType>(other), y / CCast<ScalarType>(other), z / CCast<ScalarType>(other) }; return *this; }

	template<class T>   VIDECL VIREQOUT inline Bool      operator==(const T&        other) const { return false;                                                                                                      }
	template<class T>   VIDECL VIREQOUT inline Bool      operator!=(const T&        other) const { return true;                                                                                                       }
	template<>          VIDECL VIREQOUT inline Bool      operator==(const SVector3& other) const { return CompareScalar(x, other.x) && CompareScalar(y, other.y) && CompareScalar(z, other.z);                        }
	template<>          VIDECL VIREQOUT inline Bool      operator!=(const SVector3& other) const { return !(*this == other);                                                                                          }

};

VIDECL VIREQOUT inline SVector3 FSqrt(const SVector3& v) { return v * v; }
VIDECL VIREQOUT inline ScalarType FDot(const SVector3& a, const SVector3& b) { SVector3 tmp = a * b; return tmp.x + tmp.y + tmp.z; }
VIDECL VIREQOUT inline ScalarType FLength(const SVector3& v) { return FSqrt(FDot(v, v)); }
VIDECL VIREQOUT inline ScalarType FDistance(const SVector3& a, const SVector3& b) { return FLength(b - a); }
VIDECL VIREQOUT inline SVector3 FNormalize(const SVector3& v) { return v * (1.0F / FLength(v)); }
VIDECL VIREQOUT inline SVector3 FReflect(const SVector3& i, const SVector3& n) { return i - n * FDot(n, i) * 2.0F; }
VIDECL VIREQOUT inline SVector3 FRefract(const SVector3& i, const SVector3& n, const ScalarType& eta) { auto dv(FDot(n, i)); auto k(1.0F - eta * eta * (1.0F - dv * dv)); return { (k >= 0.0F) ? (i * eta - (n * (eta * dv + FSqrt(k)))) : SVector3(0.0F) }; }
VIDECL VIREQOUT inline SVector3 FCross(const SVector3& a, const SVector3& b) { return {a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y }; }
VIDECL VIREQOUT inline SVector3 FRadians(const SVector3& v) { return { FRadians(v.x), FRadians(v.y), FRadians(v.z) }; }
VIDECL VIREQOUT inline SVector3 FDegrees(const SVector3& v) { return { FDegrees(v.x), FDegrees(v.y), FDegrees(v.z) }; }
VIDECL VIREQOUT inline SVector3 FSin(const SVector3& v) { return { FSin(v.x), FSin(v.y), FSin(v.z) }; }
VIDECL VIREQOUT inline SVector3 FCos(const SVector3& v) { return { FCos(v.x), FCos(v.y), FCos(v.z) }; }
VIDECL VIREQOUT inline SVector3 FTan(const SVector3& v) { return { FTan(v.x), FTan(v.y), FTan(v.z) }; }
VIDECL VIREQOUT inline SVector3 FArcSin(const SVector3& v) { return { FArcSin(v.x), FArcSin(v.y), FArcSin(v.z) }; }
VIDECL VIREQOUT inline SVector3 FArcCos(const SVector3& v) { return { FArcCos(v.x), FArcCos(v.y), FArcCos(v.z) }; }
VIDECL VIREQOUT inline SVector3 FArcTan(const SVector3& v) { return { FArcTan(v.x), FArcTan(v.y), FArcTan(v.z) }; }

VISRCEND

#endif //VICTORIAM_MVECTOR3_HPP
