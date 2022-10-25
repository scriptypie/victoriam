//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/Math/Common/Comparator.hpp>

#include <Victoriam/Math/Vector/FuncVector3.hpp>

VISRCBEG

Bool operator==(SVector3 a, SVector3 b)
{
	return
			(
					CComparator::Equal(a.data[0], b.data[0]) &&
					CComparator::Equal(a.data[1], b.data[1]) &&
					CComparator::Equal(a.data[2], b.data[2])
			);
}

Bool operator!=(SVector3 a, SVector3 b)
{
	return
			(
					!CComparator::Equal(a.data[0], b.data[0]) &&
					!CComparator::Equal(a.data[1], b.data[1]) &&
					!CComparator::Equal(a.data[2], b.data[2])
			);
}

Bool operator>=(SVector3 a, SVector3 b)
{
	return
			(
					a.data[0] >= b.data[0] &&
					a.data[1] >= b.data[1] &&
					a.data[2] >= b.data[2]
			);
}

Bool operator<=(SVector3 a, SVector3 b)
{
	return
			(
					a.data[0] <= b.data[0] &&
					a.data[1] <= b.data[1] &&
					a.data[2] <= b.data[2]
			);
}

Bool operator<(SVector3 a, SVector3 b)
{
	return
			(
					CComparator::Less(a.data[0], b.data[0]) &&
					CComparator::Less(a.data[1], b.data[1]) &&
					CComparator::Less(a.data[2], b.data[2])
			);
}

Bool operator>(SVector3 a, SVector3 b)
{
	return
			(
					CComparator::Greater(a.data[0], b.data[0]) &&
					CComparator::Greater(a.data[1], b.data[1]) &&
					CComparator::Greater(a.data[2], b.data[2])
			);
}

SVector3 max(SVector3 a, SVector3 b)
{
	return (a > b) ? a : b;
}

SVector3 min(SVector3 a, SVector3 b)
{
	return (a < b) ? a : b;
}

Scalar FDot(SVector3 a, SVector3 b)
{
	return
			(
					a.x * b.x + a.y * b.y + a.z * b.z
			);
}

Scalar FDot(SVector3 a, SVector2 b)
{
	return
			(
					a.x * b.x + a.y * b.y
			);
}

Scalar FDot(SVector2 a, SVector3 b)
{
	return
			(
					a.x * b.x + a.y * b.y
			);
}

SVector3 FCross(SVector3 a, SVector3 b)
{
	return
			(
					SVector3{
							a.y * b.z - a.z * b.y,
							a.z * b.x - a.x * b.z,
							a.x * b.y - a.y * b.x
					}
			);
}

SVector3 FProject(SVector3 a, SVector3 b)
{
	return
			(
					b * FDot(a, b)
			);
}

SVector3 FReject(SVector3 a, SVector3 b)
{
	return
			(
					a - b * FDot(a, b)
			);
}

Scalar FLength(SVector3 a)
{
	return
			(
#ifdef SALG_HIGH_PRECISION
					std::sqrt(
    a.data[0] * a.data[0] +
    a.data[1] * a.data[1] +
    a.data[2] * a.data[2]
    )
#else
					std::sqrtf(
							a.data[0] * a.data[0] +
							a.data[1] * a.data[1] +
							a.data[2] * a.data[2]
					)
#endif
			);
}

Scalar FLength2(SVector3 a)
{
	return FLength(a) * FLength(a);
}

Scalar FDistance(SVector3 from, SVector3 to)
{
	return FLength(
			SVector3{
					to.data[0] - from.data[0],
					to.data[1] - from.data[1],
					to.data[2] - from.data[2]
			}
	);
}

SVector3 FNormalize(SVector3 a)
{
	Scalar len = FLength(a);
	if (!len) return a;
	SVector3 b(a);
	b *= (CCast<Scalar>(1) / len);
	return b;
}

Scalar FMagnitude(SVector3 a)
{
	return
			(
#ifdef SALG_HIGH_PRECISION
					std::sqrt(dot(a, a))
#else
					std::sqrtf(FDot(a, a))
#endif
			);
}

Scalar FMagnitude2(SVector3 a)
{
	return
			(
					FDot(a, a)
			);
}

Scalar FRMagnitude(SVector3 a)
{
	return
			(
#ifdef SALG_HIGH_PRECISION
					rsqrt(dot(a, a))
#else
					rsqrt(FDot(a, a))
#endif
			);
}

SVector3 FFloor(SVector3 a)
{
	return
			{
#ifdef SALG_HIGH_PRECISION
					std::floor(a.data[0]), std::floor(a.data[1]), std::floor(a.data[2])
#else
					std::floorf(a.data[0]), std::floorf(a.data[1]), std::floorf(a.data[2])
#endif
			};
}

SVector3 FCeil(SVector3 a)
{
	return
			{
#ifdef SALG_HIGH_PRECISION
					std::ceil(a.data[0]), std::ceil(a.data[1]), std::ceil(a.data[2])
#else
					std::ceilf(a.data[0]), std::ceilf(a.data[1]), std::ceilf(a.data[2])
#endif
			};
}

std::ostream& operator<<(std::ostream& os, SVector3 v)
{
	return
			os << "("
			   << v.data[0]
			   << ", "
			   << v.data[1]
			   << ", "
			   << v.data[2]
			   << ")";
}

VISRCEND
