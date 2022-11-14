//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MATRIXFUNCTIONS_HPP
#define VICTORIAM_MATRIXFUNCTIONS_HPP

#include <Victoriam/Matemia/Base/Scalar.hpp>

VISRCBEG

struct SVector2;
struct SVector3;
struct SVector4;
typedef SVector4 SRect;
struct SMatrix4;

VIDECL VIREQOUT SMatrix4 FInverse(const SMatrix4& m);
VIDECL VIREQOUT SMatrix4 FPerspective(const ScalarType& fovy, const ScalarType& aspect, const ScalarType& zNear, const ScalarType& zFar);
VIDECL VIREQOUT SMatrix4 FOrthographic(const ScalarType& left, const ScalarType& right, const ScalarType& bottom, const ScalarType& top, const ScalarType& zNear, const ScalarType& zFar);
VIDECL VIREQOUT SMatrix4 FOrthographic(const SRect& bounds, const ScalarType& zNear, const ScalarType& zFar);

VISRCEND

#endif //VICTORIAM_MATRIXFUNCTIONS_HPP
