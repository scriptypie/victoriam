//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_VECTORBASE_HPP
#define VICTORIAM_VECTORBASE_HPP

#include <Victoriam/Math/Common/Scalar.hpp>
#include <Victoriam/Math/Common/ScalarArray.hpp>

VISRCBEG

template<UInt16 NUM_DIMENSIONS> struct VIDECL SVectorBase;

template<>
struct VIDECL SVectorBase<2>
{
	VIDECL inline static constexpr UInt16 DIM = 2;

	union
	{
		struct
		{
			Scalar x, y;
		};
		SScalarArray<2> data = {};
	};

	SVectorBase() = default;
	~SVectorBase() = default;
	VIDECL explicit SVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

template<>
struct VIDECL SVectorBase<3>
{
	VIDECL inline static constexpr UInt16 DIM = 3;

	union
	{
		struct
		{
			Scalar x, y, z;
		};
		SScalarArray<3> data = {};
	};

	SVectorBase() = default;
	~SVectorBase() = default;
	VIDECL SVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

template<>
struct VIDECL SVectorBase<4>
{
	VIDECL inline static constexpr UInt16 DIM = 4;

	union
	{
		struct
		{
			Scalar x, y, z, w;
		};
		SScalarArray<4> data = {};
	};

	SVectorBase() = default;
	~SVectorBase() = default;
	VIDECL SVectorBase(const Scalar _data[DIM])
	{
		for (Int16 i = 0; i < DIM; i++) data[i] = _data[i];
	}

};

VISRCEND

#endif //VICTORIAM_VECTORBASE_HPP
