//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR4_HPP
#define VICTORIAM_TYPEVECTOR4_HPP

#include <Victoriam/Math/Vector/TypeVector3.hpp>

VISRCBEG

struct VIDECL SVector4 : SVectorBase<4>
{
	inline SVector4() = default;
	inline ~SVector4() = default;
	inline SVector4(const SVector4&) = default;
	inline SVector4& operator=(const SVector4&) = default;
	inline SVector4(SVector4&&) = default;
	inline SVector4& operator=(SVector4&&) = default;

	VIDECL inline SVector4(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w)
			: SVectorBase(((Scalar[DIM]){x, y, z, w}))
	{}

	VIDECL inline explicit SVector4(const SVector3& v) : SVectorBase(((Scalar[DIM]){v.data[0], v.data[1], v.data[2], 0})) {}
	VIDECL inline explicit SVector4(const SVector2& v) : SVectorBase(((Scalar[DIM]){v.data[0], v.data[1], 0, 0})) {}

	VIDECL inline SVector2& xy() { return(*(SVector2*)this); }
	VIDECL inline SVector3& xyz() { return(*(SVector3*)this); }

	template<class U>
	VIDECL inline SVector4 operator + (const U& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector4 operator + (const SVector4& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector4 operator - (const U& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector4 operator - (const SVector4& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector4 operator * (const U& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector4 operator * (const SVector4& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector4 operator / (const U& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector4 operator / (const SVector4& other) {
		SVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	VIDECL inline SVector4& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	VIDECL inline SVector4& operator += (const SVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector4& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	VIDECL inline SVector4& operator -= (const SVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector4& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	VIDECL inline SVector4& operator *= (const SVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector4& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	VIDECL inline SVector4& operator /= (const SVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR4_HPP
