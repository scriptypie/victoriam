//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR3_HPP
#define VICTORIAM_TYPEVECTOR3_HPP

#include <Victoriam/Math/Vector/TypeVector2.hpp>

VISRCBEG

struct VIDECL sVector3 : sVectorBase<3>
{
	inline sVector3() = default;
	inline ~sVector3() = default;
	inline sVector3(const sVector3&) = default;
	inline sVector3& operator=(const sVector3&) = default;
	inline sVector3(sVector3&&) = default;
	inline sVector3& operator=(sVector3&&) = default;

	VIDECL inline sVector3(const Scalar& x, const Scalar& y, const Scalar& z)
			: sVectorBase(((Scalar[DIM]){x, y, z}))
	{}

	SVector2& xy()
	{
		return *(SVector2*) this;
	}

	template<class U>
	sVector3 operator + (const U& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	sVector3 operator + (const sVector3& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	sVector3 operator - (const U& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	sVector3 operator - (const sVector3& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	sVector3 operator * (const U& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	sVector3 operator * (const sVector3& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	sVector3 operator / (const U& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	sVector3 operator / (const sVector3& other) {
		sVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	sVector3& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	sVector3& operator += (const sVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	sVector3& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	sVector3& operator -= (const sVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	sVector3& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	sVector3& operator *= (const sVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	sVector3& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	sVector3& operator /= (const sVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR3_HPP
