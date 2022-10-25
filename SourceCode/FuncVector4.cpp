//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/Math/Common/Comparator.hpp>

#include <Victoriam/Math/Vector/FuncVector4.hpp>

VISRCBEG

	Bool operator==(SVector4 a, SVector4 b)
	{
		return
				(
						CComparator::Equal(a.data[0], b.data[0]) &&
						CComparator::Equal(a.data[1], b.data[1]) &&
						CComparator::Equal(a.data[2], b.data[2]) &&
						CComparator::Equal(a.data[3], b.data[3])
				);
	}

	Bool operator!=(SVector4 a, SVector4 b)
	{
		return
				(
						!CComparator::Equal(a.data[0], b.data[0]) &&
						!CComparator::Equal(a.data[1], b.data[1]) &&
						!CComparator::Equal(a.data[2], b.data[2]) &&
						!CComparator::Equal(a.data[3], b.data[3])
				);
	}

	Bool operator>=(SVector4 a, SVector4 b)
	{
		return
				(
						a.data[0] >= b.data[0] &&
						a.data[1] >= b.data[1] &&
						a.data[2] >= b.data[2] &&
						a.data[3] >= b.data[3]
				);
	}

	Bool operator<=(SVector4 a, SVector4 b)
	{
		return
				(
						a.data[0] <= b.data[0] &&
						a.data[1] <= b.data[1] &&
						a.data[2] <= b.data[2] &&
						a.data[3] <= b.data[3]
				);
	}

	Bool operator<(SVector4 a, SVector4 b)
	{
		return
				(
						CComparator::Less(a.data[0], b.data[0]) &&
						CComparator::Less(a.data[1], b.data[1]) &&
						CComparator::Less(a.data[2], b.data[2]) &&
						CComparator::Less(a.data[3], b.data[3])
				);
	}

	Bool operator>(SVector4 a, SVector4 b)
	{
		return
				(
						CComparator::Greater(a.data[0], b.data[0]) &&
						CComparator::Greater(a.data[1], b.data[1]) &&
						CComparator::Greater(a.data[2], b.data[2]) &&
						CComparator::Greater(a.data[3], b.data[3])
				);
	}

	SVector4 max(SVector4 a, SVector4 b)
	{
		return (a > b) ? a : b;
	}

	SVector4 min(SVector4 a, SVector4 b)
	{
		return (a < b) ? a : b;
	}

	Scalar FDot(SVector4 a, SVector4 b)
	{
		return
				(
						a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w
				);
	}

	Scalar FDot(SVector4 a, SVector3 b)
	{
		return
				(
						a.x * b.x + a.y * b.y + a.z * b.z
				);
	}

	Scalar FDot(SVector3 a, SVector4 b)
	{
		return
				(
						a.x * b.x + a.y * b.y + a.z * b.z
				);
	}

	Scalar FDot(SVector4 a, SVector2 b)
	{
		return
				(
						a.x * b.x + a.y * b.y
				);
	}

	Scalar FDot(SVector2 a, SVector4 b)
	{
		return
				(
						a.x * b.x + a.y * b.y
				);
	}

	SVector4 FProject(SVector4 a, SVector4 b)
	{
		return
				(
						b * FDot(a, b)
				);
	}

	SVector4 FReject(SVector4 a, SVector4 b)
	{
		return
				(
						a - b * FDot(a, b)
				);
	}

	Scalar FLength(SVector4 a)
	{
		return
				(
#ifdef SALG_HIGH_PRECISION
						std::sqrt(
        a.data[0] * a.data[0] +
        a.data[1] * a.data[1] +
        a.data[2] * a.data[2] +
        a.data[3] * a.data[3]
        )
#else
						std::sqrtf(
								a.data[0] * a.data[0] +
								a.data[1] * a.data[1] +
								a.data[2] * a.data[2] +
								a.data[3] * a.data[3]
						)
#endif
				);
	}

	Scalar FLength2(SVector4 a)
	{
		return FLength(a) * FLength(a);
	}

	SVector4 FNormalize(SVector4 a)
	{
		Scalar len = FLength(a);
		if (!len) return a;
		SVector4 b(a);
		b *= (CCast<Scalar>(1) / len);
		return b;
	}

	Scalar FMagnitude(SVector4 a)
	{
		return
				(
#ifdef SALG_HIGH_PRECISION
						std::sqrt(FDot(a, a))
#else
						std::sqrtf(FDot(a, a))
#endif
				);
	}

	Scalar FMagnitude2(SVector4 a)
	{
		return
				(
						FDot(a, a)
				);
	}

	Scalar FRMagnitude(SVector4 a)
	{
		return
				(
#ifdef SALG_HIGH_PRECISION
						rsqrt(FDot(a, a))
#else
						rsqrt(FDot(a, a))
#endif
				);
	}

	SVector4 FFloor(SVector4 a)
	{
		return
				{
#ifdef SALG_HIGH_PRECISION
						std::floor(a.data[0]), std::floor(a.data[1]), std::floor(a.data[2]), std::floor(a.data[3])
#else
						std::floorf(a.data[0]), std::floorf(a.data[1]), std::floorf(a.data[2]), std::floorf(a.data[3])
#endif
				};
	}

	SVector4 FCeil(SVector4 a)
	{
		return
				{
#ifdef SALG_HIGH_PRECISION
						std::ceil(a.data[0]), std::ceil(a.data[1]), std::ceil(a.data[2]), std::ceil(a.data[3])
#else
						std::ceilf(a.data[0]), std::ceilf(a.data[1]), std::ceilf(a.data[2]), std::ceilf(a.data[3])
#endif
				};
	}

	std::ostream& operator<<(std::ostream& os, SVector4 v)
	{
		return
				os << "("
				   << v.data[0]
				   << ", "
				   << v.data[1]
				   << ", "
				   << v.data[2]
				   << ", "
				   << v.data[3]
				   << ")";
	}

VISRCEND
