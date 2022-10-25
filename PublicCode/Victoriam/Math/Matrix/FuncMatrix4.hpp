//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_FUNCMATRIX4_HPP
#define VICTORIAM_FUNCMATRIX4_HPP

#include <Victoriam/Math/Matrix/TypeMatrix4.hpp>
#include <Victoriam/Math/Ext/TransformData.hpp>

VISRCBEG

VIDECL Bool operator==(SMatrix4 a, SMatrix4 b);
VIDECL Bool operator!=(SMatrix4 a, SMatrix4 b);
VIDECL Bool operator>=(SMatrix4 a, SMatrix4 b);
VIDECL Bool operator<=(SMatrix4 a, SMatrix4 b);
VIDECL Bool operator<(SMatrix4 a, SMatrix4 b);
VIDECL Bool operator>(SMatrix4 a, SMatrix4 b);

VIDECL SMatrix4 max(SMatrix4 a, SMatrix4 b);
VIDECL SMatrix4 min(SMatrix4 a, SMatrix4 b);

VIDECL SMatrix4 FTranslate(SVector3 translation);
VIDECL SVector3 FGetTranslation(SMatrix4 m);
VIDECL SVector3 FGetScale(SMatrix4 m);
VIDECL STransformData decompose(SMatrix4 m);
VIDECL void FOrthoNormalize(SMatrix4& m);
VIDECL SMatrix4 FTranspose(SMatrix4 m);
VIDECL SMatrix4 FScale(SVector3 s);
VIDECL SMatrix4 FRotateX(const Scalar& angle);
VIDECL SMatrix4 FRotateY(const Scalar& angle);
VIDECL SMatrix4 FRotateZ(const Scalar& angle);
VIDECL SMatrix4 FRotate(const Scalar& r, const Scalar& i, const Scalar& j, const Scalar& k);
VIDECL SMatrix4 FFrustrum(Scalar bottom, Scalar top, Scalar left, Scalar right, Scalar near, Scalar far);
VIDECL SMatrix4 FPerspectiveRH(Scalar fovY, Scalar aspect, Scalar near, Scalar far);
VIDECL SMatrix4 FPerspectiveLH(Scalar fovY, Scalar aspect, Scalar near, Scalar far);
VIDECL SMatrix4 FOrthographicRH(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far);
VIDECL SMatrix4 FOrthographicLH(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far);
VIDECL SMatrix4 FLookAt(SVector3 fromPos, SVector3 toPos, SVector3 up);
VIDECL Scalar FDeterminant(SMatrix4 m);
VIDECL SMatrix4 FInverse(SMatrix4 m);
VIDECL SMatrix4 FIdentity();

VISRCEND

#endif //VICTORIAM_FUNCMATRIX4_HPP
