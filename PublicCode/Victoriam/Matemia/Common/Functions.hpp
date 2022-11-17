//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_FUNCTIONS_HPP
#define VICTORIAM_FUNCTIONS_HPP

#include <Victoriam/Matemia/Base/Base.hpp>

VISRCBEG

VIDECL VIREQOUT SMatrix4 FInverse(const SMatrix4& m);
VIDECL VIREQOUT SMatrix4 FTranslate(const SMatrix4& m, const SVector3& v);
VIDECL VIREQOUT SMatrix4 FRotate(const SMatrix4& m, const SVector3& axis, const ScalarType& angle);
VIDECL VIREQOUT SMatrix4 FRotateX(const SMatrix4& m, const ScalarType& angle);
VIDECL VIREQOUT SMatrix4 FRotateY(const SMatrix4& m, const ScalarType& angle);
VIDECL VIREQOUT SMatrix4 FRotateZ(const SMatrix4& m, const ScalarType& angle);
VIDECL VIREQOUT SMatrix4 FScale(const SMatrix4& m, const SVector3& v);
VIDECL VIREQOUT SMatrix4 FLookAt(const SVector3& position, const SVector3& direction, const SVector3& up);
VIDECL VIREQOUT SMatrix4 FPerspective(const ScalarType& fovy, const ScalarType& aspect, const ScalarType& zNear, const ScalarType& zFar);
VIDECL VIREQOUT SMatrix4 FPerspective(const ScalarType& fovy, const ScalarType& aspect, const ScalarType& zNear);
VIDECL VIREQOUT SMatrix4 FOrthographic(const ScalarType& left, const ScalarType& right, const ScalarType& bottom, const ScalarType& top, const ScalarType& zNear, const ScalarType& zFar);
VIDECL VIREQOUT SMatrix4 FOrthographic(const SRect& bounds, const ScalarType& zNear, const ScalarType& zFar);

VIDECL VIREQOUT SMatrix4 FMatrix4(const SQuaternion& quat);
VIDECL VIREQOUT ScalarType FDot(const SQuaternion& a, const SQuaternion& b);
VIDECL VIREQOUT SQuaternion FCross(const SQuaternion& a, const SQuaternion& b);
VIDECL VIREQOUT ScalarType FLength(const SQuaternion& quat);
VIDECL VIREQOUT SQuaternion FNormalize(const SQuaternion& quat);

VISRCEND

#endif //VICTORIAM_FUNCTIONS_HPP
