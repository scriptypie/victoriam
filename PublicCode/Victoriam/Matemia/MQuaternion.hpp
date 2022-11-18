//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MQUATERNION_HPP
#define VICTORIAM_MQUATERNION_HPP

#include <Victoriam/Matemia/MMatrix4.hpp>

VISRCBEG

struct VIDECL SQuaternion {

	ScalarType x, y, z, w;

	VIDECL inline ~SQuaternion() = default;
	VIDECL inline  SQuaternion() = default;
	VIDECL inline  SQuaternion(const SQuaternion&) = default;
	VIDECL inline  SQuaternion(const ScalarType& _x, const ScalarType& _y, const ScalarType& _z, const ScalarType& _w) : x(_x), y(_y), z(_z), w(_w) {}
	VIDECL inline  SQuaternion(const ScalarType& s, const SVector3& v) : x(v.x), y(v.y), z(v.z), w(s) {}
	VIDECL inline  SQuaternion(const SVector3& ea) { auto c = FCos(ea * 0.5F); auto s = FSin(ea * 0.5F); w = c.x * c.y * c.z + s.x * s.y * s.z; x = s.x * c.y * c.z - c.x * s.y * s.z; y = c.x * s.y * c.z + s.x * c.y * s.z; z = c.x * c.y * s.z - s.x * s.y * c.z; }
	VIDECL inline  SQuaternion(const SVector3& u, const SVector3& v) { auto nunv = FSqrt(FDot(u, u) * FDot(v, v)); auto rp = nunv + FDot(u, v); SVector3 t; if (rp < 1.e-6f * nunv) { rp = 0.0F; t = FAbs(u.x) > FAbs(u.z) ? SVector3(-u.y, u.x, 0.0F) : SVector3(0.0F, -u.z, u.y); } else { t = FCross(u, v); } *this = FNormalize(SQuaternion(rp, t.x, t.y, t.z)); }

	VIDECL VIREQOUT inline ScalarType& operator[](int pos)       { return(&x)[pos]; }
	VIDECL VIREQOUT inline ScalarType  operator[](int pos) const { return(&x)[pos]; }

};

VIDECL inline CStream& operator<<(CStream& stream, const SQuaternion& quat) { return stream << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")"; }

VISRCEND

#endif //VICTORIAM_MQUATERNION_HPP
