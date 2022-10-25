//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_FUNCVECTOR4_HPP
#define VICTORIAM_FUNCVECTOR4_HPP

#include <Victoriam/Math/Vector/TypeVector4.hpp>

VISRCBEG

VIDECL Bool operator==(SVector4 a, SVector4 b);
VIDECL Bool operator!=(SVector4 a, SVector4 b);
VIDECL Bool operator>=(SVector4 a, SVector4 b);
VIDECL Bool operator<=(SVector4 a, SVector4 b);
VIDECL Bool operator<(SVector4 a, SVector4 b);
VIDECL Bool operator>(SVector4 a, SVector4 b);

VIDECL SVector4 max(SVector4 a, SVector4 b);
VIDECL SVector4 min(SVector4 a, SVector4 b);

VIDECL Scalar FDot(SVector4 a, SVector4 b);
VIDECL Scalar FDot(SVector3 a, SVector4 b);
VIDECL Scalar FDot(SVector4 a, SVector3 b);
VIDECL Scalar FDot(SVector4 a, SVector2 b);
VIDECL Scalar FDot(SVector2 a, SVector4 b);
VIDECL SVector4 FProject(SVector4 a, SVector4 b);
VIDECL SVector4 FReject(SVector4 a, SVector4 b);
VIDECL Scalar FLength(SVector4 a);
VIDECL Scalar FLength2(SVector4 a);
VIDECL SVector4 FNormalize(SVector4 a);
VIDECL SVector4 FFloor(SVector4 a);
VIDECL SVector4 FCeil(SVector4 a);
VIDECL Scalar FMagnitude(SVector4 a);
VIDECL Scalar FMagnitude2(SVector4 a);
VIDECL Scalar FRMagnitude(SVector4 a);

VIDECL std::ostream& operator<<(std::ostream& os, SVector4 v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR4_HPP
