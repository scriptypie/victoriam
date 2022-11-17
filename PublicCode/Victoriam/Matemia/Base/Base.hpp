//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_BASE_HPP
#define VICTORIAM_BASE_HPP

#include <Victoriam/Matemia/Base/Scalar.hpp>

VISRCBEG

struct  SVector2;
struct  SVector3;
struct  SVector4;
struct  SMatrix4;
struct  SQuaternion;

typedef SVector4 SRect;
typedef SVector3 SPoint3D;
typedef SVector2 SPoint2D;

struct SShape;
struct SAABB;
struct SSphere;
struct SPlane;
struct SFrustrum;

enum class ECHalfspace;

VISRCEND

#endif //VICTORIAM_BASE_HPP
