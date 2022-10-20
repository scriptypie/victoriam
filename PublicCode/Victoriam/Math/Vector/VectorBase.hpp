//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_VECTORBASE_HPP
#define VICTORIAM_VECTORBASE_HPP

#include <Victoriam/Math/Common/Scalar.hpp>
#include <Victoriam/Math/Common/ScalarArray.hpp>

VISRCBEG

template<UInt16 NUM_DIMENSIONS> struct VIDECL sVectorBase;

template<>
struct VIDECL sVectorBase<2>
{
	VIDECL inline static constexpr UInt16 DIM = 2;

	union
	{
		struct
		{
			Scalar x, y;
		};
		sScalarArray<2> data = {};
	};

	sVectorBase() = default;
	~sVectorBase() = default;
	VIDECL explicit sVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

template<>
struct VIDECL sVectorBase<3>
{
	VIDECL inline static constexpr UInt16 DIM = 3;

	union
	{
		struct
		{
			Scalar x, y, z;
		};
		sScalarArray<3> data = {};
	};

	sVectorBase() = default;
	~sVectorBase() = default;
	VIDECL sVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

template<>
struct VIDECL sVectorBase<4>
{
	VIDECL inline static constexpr UInt16 DIM = 4;

	union
	{
		struct
		{
			Scalar x, y, z, w;
		};
		sScalarArray<4> data = {};
	};

	sVectorBase() = default;
	~sVectorBase() = default;
	VIDECL sVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

VISRCEND

#endif //VICTORIAM_VECTORBASE_HPP
