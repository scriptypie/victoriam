//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR2_HPP
#define VICTORIAM_TYPEVECTOR2_HPP

#include <Victoriam/Math/Vector/VectorBase.hpp>

VISRCBEG

struct VIDECL SVector2 : sVectorBase<2>
{
	inline SVector2() = default;
	inline ~SVector2() = default;
	inline SVector2(const SVector2&) = default;
	inline SVector2& operator=(const SVector2&) = default;
	inline SVector2(SVector2&&) = default;
	inline SVector2& operator=(SVector2&&) = default;

	VIDECL inline SVector2(const Scalar& x, const Scalar& y)
		: sVectorBase(((Scalar[DIM]){x, y}))
	{}

	template<class U>
	SVector2 operator + (const U& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	SVector2 operator + (const SVector2& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	SVector2 operator - (const U& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	SVector2 operator - (const SVector2& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	SVector2 operator * (const U& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	SVector2 operator * (const SVector2& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	SVector2 operator / (const U& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	SVector2 operator / (const SVector2& other) {
		SVector2 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	SVector2& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	SVector2& operator += (const SVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	SVector2& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	SVector2& operator -= (const SVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	SVector2& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	SVector2& operator *= (const SVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	SVector2& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	SVector2& operator /= (const SVector2& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR2_HPP
