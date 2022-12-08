//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MVECTOR4_HPP
#define VICTORIAM_MVECTOR4_HPP

#include <Victoriam/Matemia/MVector3.hpp>

VISRCBEG

struct VIDECL SVector4 {
	using Array2Type = ScalarArray<2>;
	using Array3Type = ScalarArray<3>;
	using Array4Type = ScalarArray<4>;

	union {
		Array4Type data = {};
		struct {
			union {
				Array4Type xyzw;
				Array4Type rgba;
				struct {
					union {
						Array3Type xyz;
						Array3Type rgb;
						struct {
							union {
								Array2Type xy;
								Array2Type uv;
								struct {
									union {
										ScalarType x, u, r, left;
									};
									union {
										ScalarType y, v, g, right;
									};
								};
							};
							union {
								ScalarType z, s, b, bottom;
							};
						};
					};
					union {
						ScalarType w, t, a, top;
					};
				};
			};
		};
	};

	VIDECL inline ~SVector4() = default;
	VIDECL inline  SVector4() : data() {}
	VIDECL inline  SVector4(const Array2Type& other)            : data(other) {}
	VIDECL inline  SVector4(const Array3Type& other)            : data(other) {}
	VIDECL inline  SVector4(const Array4Type& other)            : data(other) {}
	VIDECL inline  SVector4(const ScalarType& v)                    : data(v, v, v, v) {}
	VIDECL inline  SVector4(const ScalarType& x, const ScalarType& y, const ScalarType& z, const ScalarType& w) : data(x, y, z, w) {}
	VIDECL inline  SVector4(const SVector2& other)                  : data(other.data) {}
	VIDECL inline  SVector4(const SVector2& a, const SVector2& b)   : data(a.x, a.y, b.x, b.y) {}
	VIDECL inline  SVector4(const SVector3& other)                  : data(other.data) {}
	VIDECL inline  SVector4(const SVector3& a, const ScalarType& b) : data(a.x, a.y, a.z, b) {}
	VIDECL inline  SVector4(const ScalarType& a, const SVector3& b) : data(a, b.x, b.y, b.z) {}
	VIDECL inline  SVector4(const SVector4& other)                  : data(other.data) {}
	VIDECL inline  SVector4(SVector2&& other) noexcept              : data(FMove(other.x), FMove(other.y)) {}
	VIDECL inline  SVector4(SVector3&& other) noexcept              : data(FMove(other.x), FMove(other.y), FMove(other.z)) {}
	VIDECL inline  SVector4(SVector4&& other) noexcept              : data(FMove(other.x), FMove(other.y), FMove(other.z), FMove(other.w)) {}
	VIDECL inline  SVector4& operator=(const SVector4& other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	VIDECL inline  SVector4& operator=(SVector4&& other) noexcept { x = FMove(other.x); y = FMove(other.y); z = FMove(other.z); w = FMove(other.w); return *this; }

						VIDECL VIREQOUT inline ScalarType& operator[](int pos) { return data[pos]; }
						VIDECL VIREQOUT inline ScalarType  operator[](int pos) const { return data[pos]; }

						VIDECL          inline SVector4    operator+ (                     ) const { return { x,           y,           z,           w            };               }
						VIDECL          inline SVector4    operator- (                     ) const { return {-x,          -y,          -z,          -w            };               }

	template<class T>   VIDECL          inline SVector4    operator+ (const T&        other) const { return { x + other,   y + other,   z + other,   w + other    };               }
	template<class T>   VIDECL          inline SVector4    operator- (const T&        other) const { return { x - other,   y - other,   z - other,   w - other    };               }
	template<class T>   VIDECL          inline SVector4    operator* (const T&        other) const { return { x * other,   y * other,   z * other,   w * other    };               }
	template<class T>   VIDECL          inline SVector4    operator/ (const T&        other) const { return { x / other,   y / other,   z / other,   w / other    };               }
	template<class T>   VIDECL          inline SVector4&   operator+=(const T&        other)       { *this ={ x + other,   y + other,   z + other,   w + other    }; return *this; }
	template<class T>   VIDECL          inline SVector4&   operator-=(const T&        other)       { *this ={ x - other,   y - other,   z - other,   w - other    }; return *this; }
	template<class T>   VIDECL          inline SVector4&   operator*=(const T&        other)       { *this ={ x * other,   y * other,   z * other,   w * other    }; return *this; }
	template<class T>   VIDECL          inline SVector4&   operator/=(const T&        other)       { *this ={ x / other,   y / other,   z / other,   w / other    }; return *this; }
	template<>          VIDECL          inline SVector4    operator+ (const SVector4& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w  };               }
	template<>          VIDECL          inline SVector4    operator- (const SVector4& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w  };               }
	template<>          VIDECL          inline SVector4    operator* (const SVector4& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w  };               }
	template<>          VIDECL          inline SVector4    operator/ (const SVector4& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w  };               }
	template<>          VIDECL          inline SVector4    operator+ (const SVector3& other) const { return { x + other.x, y + other.y, z + other.z,           w  };               }
	template<>          VIDECL          inline SVector4    operator- (const SVector3& other) const { return { x - other.x, y - other.y, z - other.z,           w  };               }
	template<>          VIDECL          inline SVector4    operator* (const SVector3& other) const { return { x * other.x, y * other.y, z * other.z,           w  };               }
	template<>          VIDECL          inline SVector4    operator/ (const SVector3& other) const { return { x / other.x, y / other.y, z / other.z,           w  };               }
	template<>          VIDECL          inline SVector4    operator+ (const SVector2& other) const { return { x + other.x, y + other.y, z,                     w  };               }
	template<>          VIDECL          inline SVector4    operator- (const SVector2& other) const { return { x - other.x, y - other.y, z,                     w  };               }
	template<>          VIDECL          inline SVector4    operator* (const SVector2& other) const { return { x * other.x, y * other.y, z,                     w  };               }
	template<>          VIDECL          inline SVector4    operator/ (const SVector2& other) const { return { x / other.x, y / other.y, z,                     w  };               }
	template<>          VIDECL          inline SVector4&   operator+=(const SVector4& other)       { *this ={ x + other.x, y + other.y, z + other.z, w + other.w  }; return *this; }
	template<>          VIDECL          inline SVector4&   operator-=(const SVector4& other)       { *this ={ x - other.x, y - other.y, z - other.z, w - other.w  }; return *this; }
	template<>          VIDECL          inline SVector4&   operator*=(const SVector4& other)       { *this ={ x * other.x, y * other.y, z * other.z, w * other.w  }; return *this; }
	template<>          VIDECL          inline SVector4&   operator/=(const SVector4& other)       { *this ={ x / other.x, y / other.y, z / other.z, w / other.w  }; return *this; }
	template<>          VIDECL          inline SVector4&   operator+=(const SVector3& other)       { *this ={ x + other.x, y + other.y, z + other.z, w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator-=(const SVector3& other)       { *this ={ x - other.x, y - other.y, z - other.z, w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator*=(const SVector3& other)       { *this ={ x * other.x, y * other.y, z * other.z, w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator/=(const SVector3& other)       { *this ={ x / other.x, y / other.y, z / other.z, w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator+=(const SVector2& other)       { *this ={ x + other.x, y + other.y, z,           w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator-=(const SVector2& other)       { *this ={ x - other.x, y - other.y, z,           w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator*=(const SVector2& other)       { *this ={ x * other.x, y * other.y, z,           w            }; return *this; }
	template<>          VIDECL          inline SVector4&   operator/=(const SVector2& other)       { *this ={ x / other.x, y / other.y, z,           w            }; return *this; }

	template<class T>   VIDECL VIREQOUT inline Bool        operator==(const T&        other) const { return false;                                                                                                              }
	template<class T>   VIDECL VIREQOUT inline Bool        operator!=(const T&        other) const { return true;                                                                                                               }
	template<>          VIDECL VIREQOUT inline Bool        operator==(const SVector4& other) const { return CompareScalar(x, other.x) && CompareScalar(y, other.y) && CompareScalar(z, other.z) && CompareScalar(w, other.w);   }
	template<>          VIDECL VIREQOUT inline Bool        operator!=(const SVector4& other) const { return !(*this == other);                                                                                                  }

};

VIDECL          inline CStream& operator<<(CStream& stream, const SVector4& v) { return stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }
VIDECL          inline OStream& operator<<(OStream& stream, const SVector4& v) { return stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")"; }

VIDECL typedef SVector4 SRect;

VIDECL VIREQOUT inline SVector4 operator+(const ScalarType& a, const SVector4& b) { return { a + b.x, a + b.y, a + b.z, a + b.w }; }
VIDECL VIREQOUT inline SVector4 operator-(const ScalarType& a, const SVector4& b) { return { a - b.x, a - b.y, a - b.z, a - b.w }; }
VIDECL VIREQOUT inline SVector4 operator*(const ScalarType& a, const SVector4& b) { return { a * b.x, a * b.y, a * b.z, a * b.w }; }
VIDECL VIREQOUT inline SVector4 operator/(const ScalarType& a, const SVector4& b) { return { a / b.x, a / b.y, a / b.z, a / b.w }; }

namespace Color {

	VIDECL inline static SVector4 Black     = { 0.0F, 0.0F, 0.0F, 1.0F };
	VIDECL inline static SVector4 White     = { 1.0F, 1.0F, 1.0F, 1.0F };
	VIDECL inline static SVector4 Red       = { 1.0F, 0.0F, 0.0F, 1.0F };
	VIDECL inline static SVector4 SoftRed   = { 0.8F, 0.2F, 0.3F, 1.0F };
	VIDECL inline static SVector4 Green     = { 0.0F, 1.0F, 0.0F, 1.0F };
	VIDECL inline static SVector4 SoftGreen = { 0.2F, 0.8F, 0.3F, 1.0F };
	VIDECL inline static SVector4 Blue      = { 0.0F, 0.0F, 1.0F, 1.0F };
	VIDECL inline static SVector4 SoftBlue  = { 0.2F, 0.3F, 0.8F, 1.0F };
	VIDECL inline static SVector4 Yellow    = { 1.0F, 1.0F, 0.0F, 1.0F };
	VIDECL inline static SVector4 SoftYellow= { 0.8F, 0.8F, 0.3F, 1.0F };

	// RGB(155, 44, 13) for example...
	template<class T> VIDECL inline static SVector4 RGB(const T& r, const T& g, const T& b) { return { CCast<ScalarType>(r) / 255.0F, CCast<ScalarType>(g) / 255.0F, CCast<ScalarType>(b) / 255.0F, 1.0F }; }
	// RGBA(155, 44, 13, 255) for example...
	template<class T> VIDECL inline static SVector4 RGBA(const T& r, const T& g, const T& b, const T& a) { return { CCast<ScalarType>(r) / 255.0F, CCast<ScalarType>(g) / 255.0F, CCast<ScalarType>(b) / 255.0F, CCast<ScalarType>(a) / 255.0F }; }
}

VIDECL VIREQOUT inline SVector4     FSqrt       (const SVector4& v                                          ) { return v * v; }
VIDECL VIREQOUT inline ScalarType   FDot        (const SVector4& a, const SVector4& b                       ) { SVector4 tmp = a * b; return (tmp.x + tmp.y) + (tmp.z + tmp.w); }
VIDECL VIREQOUT inline ScalarType   FLength     (const SVector4& v                                          ) { return FSqrt(FDot(v, v)); }
VIDECL VIREQOUT inline ScalarType   FDistance   (const SVector4& a, const SVector4& b                       ) { return FLength(b - a); }
VIDECL VIREQOUT inline SVector4     FNormalize  (const SVector4& v                                          ) { return v * (1.0F / FLength(v)); }
VIDECL VIREQOUT inline SVector4     FReflect    (const SVector4& i, const SVector4& n                       ) { return i - n * FDot(n, i) * 2.0F; }
VIDECL VIREQOUT inline SVector4     FRefract    (const SVector4& i, const SVector4& n, const ScalarType& eta) { ScalarType dv(FDot(n, i)); auto k(1.0F - eta * eta * (1.0F - dv * dv)); return { (k >= 0.0F) ? (i * eta - (n * (eta * dv + FSqrt(k)))) : SVector4(0.0F) }; }
VIDECL VIREQOUT inline SVector4     FRadians    (const SVector4& v                                          ) { return { FRadians(v.x), FRadians(v.y), FRadians(v.z), FRadians(v.w) }; }
VIDECL VIREQOUT inline SVector4     FDegrees    (const SVector4& v                                          ) { return { FDegrees(v.x), FDegrees(v.y), FDegrees(v.z), FDegrees(v.w) }; }
VIDECL VIREQOUT inline SVector4     FSin        (const SVector4& v                                          ) { return { FSin(v.x), FSin(v.y), FSin(v.z), FSin(v.w) }; }
VIDECL VIREQOUT inline SVector4     FCos        (const SVector4& v                                          ) { return { FCos(v.x), FCos(v.y), FCos(v.z), FCos(v.w) }; }
VIDECL VIREQOUT inline SVector4     FTan        (const SVector4& v                                          ) { return { FTan(v.x), FTan(v.y), FTan(v.z), FTan(v.w) }; }
VIDECL VIREQOUT inline SVector4     FArcSin     (const SVector4& v                                          ) { return { FArcSin(v.x), FArcSin(v.y), FArcSin(v.z), FArcSin(v.w) }; }
VIDECL VIREQOUT inline SVector4     FArcCos     (const SVector4& v                                          ) { return { FArcCos(v.x), FArcCos(v.y), FArcCos(v.z), FArcCos(v.w) }; }
VIDECL VIREQOUT inline SVector4     FArcTan     (const SVector4& v                                          ) { return { FArcTan(v.x), FArcTan(v.y), FArcTan(v.z), FArcTan(v.w) }; }

VISRCEND

#endif //VICTORIAM_MVECTOR4_HPP
