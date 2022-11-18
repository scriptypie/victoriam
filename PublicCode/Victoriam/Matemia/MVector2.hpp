//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_MVECTOR2_HPP
#define VICTORIAM_MVECTOR2_HPP

#include <Victoriam/Matemia/Base/Base.hpp>
#include <Victoriam/Matemia/Common/Functions.hpp>

VISRCBEG

struct VIDECL SVector2 {
	union {
		ScalarArray<2> data = {};
		struct {
			union {
				ScalarArray<2> xy;
				ScalarArray<2> uv;
				struct {
					union {
						ScalarType x, u;
					};
					union {
						ScalarType y, v;
					};
				};
			};
		};
	};

	VIDECL inline static    ScalarArray<2> Zero = { 0.0F,  0.0F };
	VIDECL inline static    ScalarArray<2> One  = { 1.0F,  1.0F };
	VIDECL inline static    ScalarArray<2> Up   = { 0.0F,  1.0F };
	VIDECL inline static    ScalarArray<2> Right= { 1.0F,  0.0F };
	VIDECL inline static    ScalarArray<2> Down = { 0.0F, -1.0F };
	VIDECL inline static    ScalarArray<2> Left=  {-1.0F,  0.0F };

	VIDECL inline ~SVector2() = default;
	VIDECL inline  SVector2() : data() {}
	VIDECL inline  SVector2(const ScalarArray<2>& other) : data(other) {}
	VIDECL inline  SVector2(const ScalarType& v) : data(v, v) {}
	VIDECL inline  SVector2(const ScalarType& x, const ScalarType& y) : data{x, y} {}
	VIDECL inline  SVector2(const SVector2& other) : data(other.data) {}
	VIDECL inline  SVector2(SVector2&& other) noexcept : x(FMove(other.x)), y(FMove(other.y)) {}
	VIDECL inline  SVector2& operator=(const SVector2& other) { x = other.x; y = other.y; return *this; }
	VIDECL inline  SVector2& operator=(SVector2&& other) noexcept { x = FMove(other.x); y = FMove(other.y); return *this; }

						VIDECL VIREQOUT inline  ScalarType& operator[](int pos) { return data[pos]; }
						VIDECL VIREQOUT inline  ScalarType  operator[](int pos) const { return data[pos]; }

						VIDECL VIREQOUT inline  SVector2  operator+ (                 ) const { return { x, y }; }
						VIDECL VIREQOUT inline  SVector2  operator- (                 ) const { return { -x, -y }; }

	template<class T>   VIDECL VIREQOUT inline  SVector2  operator+ (const T       & b) const { return  { x + CCast<ScalarType>(b), y + CCast<ScalarType>(b) };               }
	template<class T>   VIDECL VIREQOUT inline  SVector2  operator- (const T       & b) const { return  { x - CCast<ScalarType>(b), y - CCast<ScalarType>(b) };               }
	template<class T>   VIDECL VIREQOUT inline  SVector2  operator* (const T       & b) const { return  { x * CCast<ScalarType>(b), y * CCast<ScalarType>(b) };               }
	template<class T>   VIDECL VIREQOUT inline  SVector2  operator/ (const T       & b) const { return  { x / CCast<ScalarType>(b), y / CCast<ScalarType>(b) };               }
	template<class T>   VIDECL          inline  SVector2& operator+=(const T       & b)       { *this = { x + CCast<ScalarType>(b), y + CCast<ScalarType>(b) }; return *this; }
	template<class T>   VIDECL          inline  SVector2& operator-=(const T       & b)       { *this = { x - CCast<ScalarType>(b), y - CCast<ScalarType>(b) }; return *this; }
	template<class T>   VIDECL          inline  SVector2& operator*=(const T       & b)       { *this = { x * CCast<ScalarType>(b), y * CCast<ScalarType>(b) }; return *this; }
	template<class T>   VIDECL          inline  SVector2& operator/=(const T       & b)       { *this = { x / CCast<ScalarType>(b), y / CCast<ScalarType>(b) }; return *this; }
	template<>          VIDECL VIREQOUT inline  SVector2  operator+ (const SVector2& b) const { return  { x + b.x,                  y + b.y                  };               }
	template<>          VIDECL VIREQOUT inline  SVector2  operator- (const SVector2& b) const { return  { x - b.x,                  y - b.y                  };               }
	template<>          VIDECL VIREQOUT inline  SVector2  operator* (const SVector2& b) const { return  { x * b.x,                  y * b.y                  };               }
	template<>          VIDECL VIREQOUT inline  SVector2  operator/ (const SVector2& b) const { return  { x / b.x,                  y / b.y                  };               }
	template<>          VIDECL          inline  SVector2& operator+=(const SVector2& b)       { *this = { x + b.x,                  y + b.y                  }; return *this; }
	template<>          VIDECL          inline  SVector2& operator-=(const SVector2& b)       { *this = { x - b.x,                  y - b.y                  }; return *this; }
	template<>          VIDECL          inline  SVector2& operator*=(const SVector2& b)       { *this = { x * b.x,                  y * b.y                  }; return *this; }
	template<>          VIDECL          inline  SVector2& operator/=(const SVector2& b)       { *this = { x / b.x,                  y / b.y                  }; return *this; }

	template<class T>   VIDECL VIREQOUT inline Bool       operator==(const T       &  ) const { return false;                                                                 }
	template<class T>   VIDECL VIREQOUT inline Bool       operator!=(const T       &  ) const { return true;                                                                  }
	template<>          VIDECL VIREQOUT inline Bool       operator==(const SVector2& b) const { return CompareScalar(x, b.x) && CompareScalar(y, b.y);                        }
	template<>          VIDECL VIREQOUT inline Bool       operator!=(const SVector2& b) const { return !(*this == b);                                                         }
};

VIDECL          inline CStream& operator<<(CStream& stream, const SVector2& v) { return stream << "(" << v.x << ", " << v.y << ")"; }

VIDECL VIREQOUT inline SVector2 operator+(const ScalarType& a, const SVector2& b) { return { a + b.x, a + b.y }; }
VIDECL VIREQOUT inline SVector2 operator-(const ScalarType& a, const SVector2& b) { return { a - b.x, a - b.y }; }
VIDECL VIREQOUT inline SVector2 operator*(const ScalarType& a, const SVector2& b) { return { a * b.x, a * b.y }; }
VIDECL VIREQOUT inline SVector2 operator/(const ScalarType& a, const SVector2& b) { return { a / b.x, a / b.y }; }

VIDECL VIREQOUT inline SVector2     FSqrt       (const SVector2& v                                          ) { return v * v; }
VIDECL VIREQOUT inline ScalarType   FDot        (const SVector2& a, const SVector2& b                       ) { SVector2 tmp = a * b; return tmp.x + tmp.y; }
VIDECL VIREQOUT inline ScalarType   FLength     (const SVector2& v                                          ) { return FSqrt(FDot(v, v)); }
VIDECL VIREQOUT inline ScalarType   FDistance   (const SVector2& a, const SVector2& b                       ) { return FLength(b - a); }
VIDECL VIREQOUT inline SVector2     FNormalize  (const SVector2& v                                          ) { return v * (1.0F / FLength(v)); }
VIDECL VIREQOUT inline SVector2     FReflect    (const SVector2& i, const SVector2& n                       ) { return i - n * FDot(n, i) * 2.0F; }
VIDECL VIREQOUT inline SVector2     FRefract    (const SVector2& i, const SVector2& n, const ScalarType& eta) { auto dv(FDot(n, i)); auto k(1.0F - eta * eta * (1.0F - dv * dv)); return { (k >= 0.0F) ? (i * eta - (n * (eta * dv + FSqrt(k)))) : SVector2(0.0F) }; }
VIDECL VIREQOUT inline SVector2     FRadians    (const SVector2& v                                          ) { return { FRadians(v.x), FRadians(v.y) }; }
VIDECL VIREQOUT inline SVector2     FDegrees    (const SVector2& v                                          ) { return { FDegrees(v.x), FDegrees(v.y) }; }
VIDECL VIREQOUT inline SVector2     FSin        (const SVector2& v                                          ) { return { FSin(v.x), FSin(v.y) }; }
VIDECL VIREQOUT inline SVector2     FCos        (const SVector2& v                                          ) { return { FCos(v.x), FCos(v.y) }; }
VIDECL VIREQOUT inline SVector2     FTan        (const SVector2& v                                          ) { return { FTan(v.x), FTan(v.y) }; }
VIDECL VIREQOUT inline SVector2     FArcSin     (const SVector2& v                                          ) { return { FArcSin(v.x), FArcSin(v.y) }; }
VIDECL VIREQOUT inline SVector2     FArcCos     (const SVector2& v                                          ) { return { FArcCos(v.x), FArcCos(v.y) }; }
VIDECL VIREQOUT inline SVector2     FArcTan     (const SVector2& v                                          ) { return { FArcTan(v.x), FArcTan(v.y) }; }

VISRCEND

#endif //VICTORIAM_MVECTOR2_HPP
