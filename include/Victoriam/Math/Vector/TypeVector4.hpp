//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR4_HPP
#define VICTORIAM_TYPEVECTOR4_HPP

#include <Victoriam/Math/Vector/TypeVector3.hpp>

VISRCBEG

struct VIDECL sVector4 : sVectorBase<4>
{
	inline sVector4() = default;
	inline ~sVector4() = default;
	inline sVector4(const sVector4&) = default;
	inline sVector4& operator=(const sVector4&) = default;
	inline sVector4(sVector4&&) = default;
	inline sVector4& operator=(sVector4&&) = default;

	VIDECL inline sVector4(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w)
			: sVectorBase(((Scalar[DIM]){x, y, z, w}))
	{}

	VIDECL inline explicit sVector4(const sVector3& v) : sVectorBase(((Scalar[DIM]){v.data[0], v.data[1], v.data[2], 0})) {}
	VIDECL inline explicit sVector4(const sVector2& v) : sVectorBase(((Scalar[DIM]){v.data[0], v.data[1], 0, 0})) {}

	VIDECL inline sVector2& xy() { return(*(sVector2*)this); }
	VIDECL inline sVector3& xyz() { return(*(sVector3*)this); }

	template<class U>
	sVector4 operator + (const U& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	sVector4 operator + (const sVector4& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	sVector4 operator - (const U& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	sVector4 operator - (const sVector4& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	sVector4 operator * (const U& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	sVector4 operator * (const sVector4& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	sVector4 operator / (const U& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	sVector4 operator / (const sVector4& other) {
		sVector4 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	sVector4& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	sVector4& operator += (const sVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	sVector4& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	sVector4& operator -= (const sVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	sVector4& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	sVector4& operator *= (const sVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	sVector4& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	sVector4& operator /= (const sVector4& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR4_HPP
