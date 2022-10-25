//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_TYPEVECTOR3_HPP
#define VICTORIAM_TYPEVECTOR3_HPP

#include <Victoriam/Math/Vector/TypeVector2.hpp>

VISRCBEG

struct VIDECL SVector3 : SVectorBase<3>
{
	inline SVector3() = default;
	inline ~SVector3() = default;
	inline SVector3(const SVector3&) = default;
	inline SVector3& operator=(const SVector3&) = default;
	inline SVector3(SVector3&&) = default;
	inline SVector3& operator=(SVector3&&) = default;

	VIDECL inline SVector3(const Scalar& x, const Scalar& y, const Scalar& z)
			: SVectorBase(((Scalar[DIM]){x, y, z}))
	{}

	VIDECL inline SVector2& xy()
	{
		return *(SVector2*) this;
	}

	template<class U>
	VIDECL inline SVector3 operator + (const U& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector3 operator + (const SVector3& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector3 operator - (const U& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector3 operator - (const SVector3& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] - other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector3 operator * (const U& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector3 operator * (const SVector3& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] * other.data[i];
		return result;
	}

	template<class U>
	VIDECL inline SVector3 operator / (const U& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / static_cast<Scalar>(other);
		return result;
	}

	VIDECL inline SVector3 operator / (const SVector3& other) {
		SVector3 result = {};
		for (short i = 0; i < DIM; i++)
			result.data[i] = data[i] / other.data[i];
		return result;
	}


	template<class U>
	VIDECL inline SVector3& operator += (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other;
		return *this;
	}

	VIDECL inline SVector3& operator += (const SVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] += other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector3& operator -= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other;
		return *this;
	}

	VIDECL inline SVector3& operator -= (const SVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] -= other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector3& operator *= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other;
		return *this;
	}

	VIDECL inline SVector3& operator *= (const SVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] *= other.data[i];
		return *this;
	}

	template<class U>
	VIDECL inline SVector3& operator /= (const U& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other;
		return *this;
	}

	VIDECL inline SVector3& operator /= (const SVector3& other) {
		for (short i = 0; i < DIM; i++)
			data[i] /= other.data[i];
		return *this;
	}
};

VISRCEND

#endif //VICTORIAM_TYPEVECTOR3_HPP
