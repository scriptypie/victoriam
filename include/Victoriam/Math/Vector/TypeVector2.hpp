//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR2_HPP
#define VICTORIAM_TYPEVECTOR2_HPP

#include <Victoriam/Math/Vector/VectorBase.hpp>

VISRCBEG

struct VIDECL sVector2 : sVectorBase<2>
{
	inline sVector2() = default;
	inline ~sVector2() = default;
	inline sVector2(const sVector2&) = default;
	inline sVector2& operator=(const sVector2&) = default;
	inline sVector2(sVector2&&) = default;
	inline sVector2& operator=(sVector2&&) = default;

	VIDECL inline sVector2(const Scalar& x, const Scalar& y)
		: sVectorBase(((Scalar[DIM]){x, y}))
	{}

	template<class U>
	sVector2 operator + (const U& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	sVector2 operator + (const sVector2& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	sVector2 operator - (const U& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	sVector2 operator - (const sVector2& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	sVector2 operator * (const U& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	sVector2 operator * (const sVector2& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	sVector2 operator / (const U& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	sVector2 operator / (const sVector2& other) {
		sVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	sVector2& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	sVector2& operator += (const sVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	sVector2& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	sVector2& operator -= (const sVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	sVector2& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	sVector2& operator *= (const sVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	sVector2& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	sVector2& operator /= (const sVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR2_HPP
