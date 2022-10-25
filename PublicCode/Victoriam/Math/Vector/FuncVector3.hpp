//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_FUNCVECTOR3_HPP
#define VICTORIAM_FUNCVECTOR3_HPP

#include <Victoriam/Math/Vector/TypeVector3.hpp>

VISRCBEG

VIDECL Bool operator==(SVector3 a, SVector3 b);
VIDECL Bool operator!=(SVector3 a, SVector3 b);
VIDECL Bool operator>=(SVector3 a, SVector3 b);
VIDECL Bool operator<=(SVector3 a, SVector3 b);
VIDECL Bool operator<(SVector3 a, SVector3 b);
VIDECL Bool operator>(SVector3 a, SVector3 b);

VIDECL SVector3 max(SVector3 a, SVector3 b);
VIDECL SVector3 min(SVector3 a, SVector3 b);

VIDECL Scalar FDot(SVector3 a, SVector3 b);
VIDECL Scalar FDot(SVector3 a, SVector2 b);
VIDECL Scalar FDot(SVector2 a, SVector3 b);
VIDECL SVector3 FCross(SVector3 a, SVector3 b);
VIDECL SVector3 FProject(SVector3 a, SVector3 b);
VIDECL SVector3 FReject(SVector3 a, SVector3 b);
VIDECL Scalar FLength(SVector3 a);
VIDECL Scalar FLength2(SVector3 a);
VIDECL Scalar FDistance(SVector3 from, SVector3 to);
VIDECL SVector3 FNormalize(SVector3 a);
VIDECL SVector3 FFloor(SVector3 a);
VIDECL SVector3 FCeil(SVector3 a);
VIDECL Scalar FMagnitude(SVector3 a);
VIDECL Scalar FMagnitude2(SVector3 a);
VIDECL Scalar FRMagnitude(SVector3 a);

VIDECL std::ostream& operator<<(std::ostream& os, SVector3 v);

VISRCEND

#endif //VICTORIAM_FUNCVECTOR3_HPP
