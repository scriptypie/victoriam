//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MMATRIX4_HPP
#define VICTORIAM_MMATRIX4_HPP

#include <Victoriam/Matemia/MVector4.hpp>

VISRCBEG

struct VIDECL SMatrix4 {
	VIDECL typedef SVector4 ColumnType;
	VIDECL typedef SVector4 RowType;

	ColumnType value[4] = {}; // column-major

	VIDECL inline ~SMatrix4() = default;
	VIDECL inline  SMatrix4() = default;
	VIDECL inline  SMatrix4(const ScalarType& x) : value{ColumnType(x, 0.0F, 0.0F, 0.0F), ColumnType(0.0F, x, 0.0F, 0.0F), ColumnType(0.0F, 0.0F, x, 0.0F), ColumnType(0.0F, 0.0F, 0.0F, x)} {}
	VIDECL inline  SMatrix4(const ScalarType& x0, const ScalarType& y0, const ScalarType& z0, const ScalarType& w0,
							const ScalarType& x1, const ScalarType& y1, const ScalarType& z1, const ScalarType& w1,
							const ScalarType& x2, const ScalarType& y2, const ScalarType& z2, const ScalarType& w2,
							const ScalarType& x3, const ScalarType& y3, const ScalarType& z3, const ScalarType& w3)
							: value{
									ColumnType(x0, y0, z0, w0),
									ColumnType(x1, y1, z1, w1),
									ColumnType(x2, y2, z2, w2),
									ColumnType(x3, y3, z3, w3)}
							{}
	VIDECL inline  SMatrix4(const ColumnType& v0, const ColumnType& v1, const ColumnType& v2, const ColumnType& v3) : value{v0, v1, v2, v3} {}
	template<class X0, class Y0, class Z0, class W0,
			class X1, class Y1, class Z1, class W1,
			class X2, class Y2, class Z2, class W2,
			class X3, class Y3, class Z3, class W3>
	VIDECL inline  SMatrix4(const X0& x0, const Y0& y0, const Z0& z0, const W0& w0,
							const X1& x1, const Y1& y1, const Z1& z1, const W1& w1,
							const X2& x2, const Y2& y2, const Z2& z2, const W2& w2,
							const X3& x3, const Y3& y3, const Z3& z3, const W3& w3)
							: value{
									ColumnType(x0, y0, z0, w0),
									ColumnType(x1, y1, z1, w1),
									ColumnType(x2, y2, z2, w2),
									ColumnType(x3, y3, z3, w3)}
							{}
	VIDECL inline  SMatrix4(const SMatrix4& other) : value{ColumnType(other[0]), ColumnType(other[1]), ColumnType(other[2]), ColumnType(other[3])} {}
	VIDECL inline  SMatrix4& operator=(const SMatrix4& other) { value[0] = other[0]; value[1] = other[1]; value[2] = other[2]; value[3] = other[3]; return *this; }
	VIDECL inline  SMatrix4& operator=(SMatrix4&& other) noexcept { value[0] = FMove(other[0]); value[1] = FMove(other[1]); value[2] = FMove(other[2]); value[3] = FMove(other[3]); return *this; }

	VIDECL VIREQOUT inline SMatrix4  operator+() const { return *this; }
	VIDECL VIREQOUT inline SMatrix4  operator-() const { return { -value[0], -value[1], -value[2], -value[3] }; }

	template<class T> VIDECL VIREQOUT inline SMatrix4& operator+=(const T       & other) { *this = { value[0] + other,    value[1] + other,    value[2] + other,    value[3] + other    }; return *this; }
	template<class T> VIDECL VIREQOUT inline SMatrix4& operator-=(const T       & other) { *this = { value[0] - other,    value[1] - other,    value[2] - other,    value[3] - other    }; return *this; }
	template<class T> VIDECL VIREQOUT inline SMatrix4& operator*=(const T       & other) { *this = { value[0] * other,    value[1] * other,    value[2] * other,    value[3] * other    }; return *this; }
	template<class T> VIDECL VIREQOUT inline SMatrix4& operator/=(const T       & other) { *this = { value[0] / other,    value[1] / other,    value[2] / other,    value[3] / other    }; return *this; }
	template<>        VIDECL VIREQOUT inline SMatrix4& operator+=(const SMatrix4& other) { *this = { value[0] + other[0], value[1] + other[1], value[2] + other[2], value[3] + other[3] }; return *this; }
	template<>        VIDECL VIREQOUT inline SMatrix4& operator-=(const SMatrix4& other) { *this = { value[0] - other[0], value[1] - other[1], value[2] - other[2], value[3] - other[3] }; return *this; }
	template<>        VIDECL VIREQOUT inline SMatrix4& operator*=(const SMatrix4& other) { return (*this = *this * other); }
	template<>        VIDECL VIREQOUT inline SMatrix4& operator/=(const SMatrix4& other) { return *this *= FInverse(other); }

	template<class T> VIDECL VIREQOUT inline SMatrix4  operator+(const T       & other) const { return { value[0] + other,          value[1] + other,          value[2] + other,          value[3] + other          }; }
	template<class T> VIDECL VIREQOUT inline SMatrix4  operator-(const T       & other) const { return { value[0] - other,          value[1] - other,          value[2] - other,          value[3] - other          }; }
	template<class T> VIDECL VIREQOUT inline SMatrix4  operator*(const T       & other) const { return { value[0] * other,          value[1] * other,          value[2] * other,          value[3] * other          }; }
	template<class T> VIDECL VIREQOUT inline SMatrix4  operator/(const T       & other) const { return { value[0] / other,          value[1] / other,          value[2] / other,          value[3] / other          }; }
	template<>        VIDECL VIREQOUT inline SMatrix4  operator+(const SMatrix4& other) const { return { value[0] + other.value[0], value[1] + other.value[1], value[2] + other.value[2], value[3] + other.value[3] }; }
	template<>        VIDECL VIREQOUT inline SMatrix4  operator-(const SMatrix4& other) const { return { value[0] - other.value[0], value[1] - other.value[1], value[2] - other.value[2], value[3] - other.value[3] }; }
	template<>        VIDECL VIREQOUT inline SMatrix4  operator*(const SMatrix4& other) const { return { value[0] * other[0][0] + value[1] * other[0][1] + value[2] * other[0][2] + value[3] * other[0][3],
																							             value[0] * other[1][0] + value[1] * other[1][1] + value[2] * other[1][2] + value[3] * other[1][3],
																							             value[0] * other[2][0] + value[1] * other[2][1] + value[2] * other[2][2] + value[3] * other[2][3],
																							             value[0] * other[3][0] + value[1] * other[3][1] + value[2] * other[3][2] + value[3] * other[3][3] }; }

	VIDECL inline ColumnType& operator[](int pos)       { return value[pos]; }
	VIDECL inline ColumnType  operator[](int pos) const { return value[pos]; }

};

VIDECL VIREQOUT inline typename SMatrix4::ColumnType operator*(const SMatrix4& m, const typename SMatrix4::RowType& v) { const auto Mov0(v[0]); const auto Mov1(v[1]); const auto Mul0 = m[0] * Mov0; const auto Mul1 = m[1] * Mov1; const auto Add0 = Mul0 + Mul1; const auto Mov2(v[2]); const auto Mov3(v[3]); const auto Mul2 = m[2] * Mov2; const auto Mul3 = m[3] * Mov3; const auto Add1 = Mul2 + Mul3; const auto Add2 = Add0 + Add1; return FMove(Add2); }

VISRCEND

#endif //VICTORIAM_FUNCTIONS_HPP
