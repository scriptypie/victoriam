//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/Math/Matrix/FuncMatrix4.hpp>
#include "Victoriam/Math/Vector/FuncVector3.hpp"

VISRCBEG

Bool operator==(SMatrix4 a, SMatrix4 b)
{
	for (auto i = 0; i < SMatrix4::NUMELMS; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

Bool operator!=(SMatrix4 a, SMatrix4 b)
{
	return !(a == b);
}

Bool operator>=(SMatrix4 a, SMatrix4 b)
{
	size_t c = 0;
	for (auto i = 0; i < SMatrix4::NUMELMS; i++)
		if (a.data[i] >= b.data[i])
			c++;
	return c == SMatrix4::NUMELMS;
}

Bool operator<=(SMatrix4 a, SMatrix4 b)
{
	size_t c = 0;
	for (auto i = 0; i < SMatrix4::NUMELMS; i++)
		if (a.data[i] <= b.data[i])
			c++;
	return c == SMatrix4::NUMELMS;
}

Bool operator<(SMatrix4 a, SMatrix4 b)
{
	size_t c = 0;
	for (auto i = 0; i < SMatrix4::NUMELMS; i++)
		if (a.data[i] < b.data[i])
			c++;
	return c == SMatrix4::NUMELMS;
}

Bool operator>(SMatrix4 a, SMatrix4 b)
{
	size_t c = 0;
	for (auto i = 0; i < SMatrix4::NUMELMS; i++)
		if (a.data[i] > b.data[i])
			c++;
	return c == SMatrix4::NUMELMS;
}

SMatrix4 max(SMatrix4 a, SMatrix4 b)
{
	if (a == b) return a;
	return (a > b) ? a : b;
}

SMatrix4 min(SMatrix4 a, SMatrix4 b)
{
	if (a == b) return a;
	return (a < b) ? a : b;
}

SMatrix4 FTranslate(SVector3 translation)
{
	SMatrix4 t;
	t.m[0][3] = translation.x;
	t.m[1][3] = translation.y;
	t.m[2][3] = translation.z;
	return t;
}

SVector3 FGetTranslation(SMatrix4 m)
{
	return { m.m[0][3], m.m[1][3], m.m[2][3] };
}

SVector3 FGetScale(SMatrix4 m)
{
	SVector3 v(
			FMagnitude({m.m[0][0], m.m[0][1], m.m[0][2]}),
			FMagnitude({m.m[1][0], m.m[1][1], m.m[1][2]}),
			FMagnitude({m.m[2][0], m.m[2][1], m.m[2][2]})
	);
	return v;
}

STransformData FDecompose(SMatrix4 m)
{
	SMatrix4 mat = FTranspose(m);
	STransformData t;
	t.Scale.data[0] = FMagnitude({mat.m[0][0], mat.m[0][1], mat.m[0][2]});
	t.Scale.data[1] = FMagnitude({mat.m[1][0], mat.m[1][1], mat.m[1][2]});
	t.Scale.data[2] = FMagnitude({mat.m[2][0], mat.m[2][1], mat.m[2][2]});

	FOrthoNormalize(mat);

	t.Rotation.data[0] = atan2(mat.m[1][2], mat.m[2][2]);
	t.Rotation.data[1] = atan2(-mat.m[0][2], sqrt(mat.m[1][2] * mat.m[1][2] + mat.m[2][2] * mat.m[2][2]));
	t.Rotation.data[2] = atan2(mat.m[0][1], mat.m[0][0]);

	t.Translation.data[0] = mat.m[3][0];
	t.Translation.data[1] = mat.m[3][1];
	t.Translation.data[2] = mat.m[3][2];

	return t;
}

void FOrthoNormalize(SMatrix4& m)
{
	SVector3 right(m.m[0][0], m.m[1][0], m.m[2][0]);
	FNormalize(right);

	m.m[0][0] = right.x;
	m.m[1][0] = right.y;
	m.m[2][0] = right.z;

	SVector3 up(m.m[0][1], m.m[1][1], m.m[2][1]);
	FNormalize(up);
	m.m[0][1] = up.x;
	m.m[1][1] = up.y;
	m.m[2][1] = up.z;

	SVector3 dir(m.m[0][2], m.m[1][2], m.m[2][2]);
	FNormalize(dir);
	m.m[0][2] = dir.x;
	m.m[1][2] = dir.y;
	m.m[2][2] = dir.z;
}

SMatrix4 FTranspose(SMatrix4 m)
{
	SMatrix4 t;
	for (auto l = 0; l < 4; l++)
		for (auto c = 0; c < 4; c++)
			t.m[l][c] = m.m[c][l];
	return t;
}

SMatrix4 FScale(SVector3 s)
{
	SMatrix4 t;
	t.m[0][0] = s.x;
	t.m[1][1] = s.y;
	t.m[2][2] = s.z;
	return t;
}

SMatrix4 FRotateX(const Scalar & angle)
{
	SMatrix4 t;
	t.m[1][1] =  cos(angle);
	t.m[1][2] = -sin(angle);
	t.m[2][1] =  sin(angle);
	t.m[2][2] =  cos(angle);
	return t;
}

SMatrix4 FRotateY(const Scalar & angle)
{
	SMatrix4 t;
	t.m[0][0] =  cos(angle);
	t.m[0][2] =  sin(angle);
	t.m[2][0] = -sin(angle);
	t.m[2][2] =  cos(angle);
	return t;
}

SMatrix4 FRotateZ(const Scalar & angle)
{
	SMatrix4 t;
	t.m[0][0] =  cos(angle);
	t.m[0][1] = -sin(angle);
	t.m[1][0] =  sin(angle);
	t.m[1][1] =  cos(angle);
	return t;
}

SMatrix4 FRotate(const Scalar & r, const Scalar & i, const Scalar & j, const Scalar & k)
{
	SMatrix4 t(
			1 - 2 * j * j - 2 * k * k,
			2 * i * j - 2 * k * r,
			2 * i * k + 2 * j * r,
			0.0f,

			2 * i * j + 2 * r * k,
			1 - 2 * i * i - 2 * k * k,
			2 * j * k - 2 * r * i,
			0.0f,

			2 * i * k - 2 * r * j,
			2 * j * k + 2 * r * i,
			1 - 2 * i * i - 2 * j * j,
			0.0f,

			0.0f,
			0.0f,
			0.0f,
			1.0f
	);
	return t;
}

SMatrix4 FFrustrum(Scalar bottom, Scalar top, Scalar left, Scalar right, Scalar near, Scalar far)
{
	SMatrix4 t(
			2.0f * near / (right - 1),
			0.0f,
			0.0f,
			0.0f,

			0.0f,
			2.0f * near / (top - bottom),
			0.0f,
			0.0f,

			(right + left) / (right - left),
			(top + bottom) / (top - bottom),
			-(far + near) / (far - near),
			-1.0f,

			0.0f,
			0.0f,
			-2.0f * far * near / (far - near),
			0.0f
	);
	return t;
}

SMatrix4 FPerspectiveRH(Scalar fovY, Scalar aspect, Scalar near, Scalar far)
{
	Scalar tanHalfFovY = tan(fovY / 2);
	SMatrix4 t(
			1.0f / (tanHalfFovY * aspect),
			0.0f,
			0.0f,
			0.0f,

			0.0f,
			1 / tanHalfFovY,
			0.0f,
			0.0f,

			0.0f,
			0.0f,
			far / (near - far),
			-1.0f,

			0.0f,
			0.0f,
			-(far * near) / (far - near),
			0.0f
	);
	return t;
}

SMatrix4 FPerspectiveLH(Scalar fovY, Scalar aspect, Scalar near, Scalar far)
{
	Scalar sinFov = sin(fovY * 0.5);
	Scalar cosFov = cos(fovY * 0.5);
	Scalar height = cosFov / sinFov;
	Scalar width = height / aspect;
	Scalar fRange = far / (far - near);

	SMatrix4 tmp
			(
					width, 0, 0, 0,
					0, height, 0, 0,
					0, 0, fRange, 0,
					0, 0, -fRange * near, 0
			);
	return tmp;
}

SMatrix4 FOrthographicRH(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far)
{
	SMatrix4 t(
			2 / (right - left),
			0.0f,
			0.0f,
			0.0f,

			0.0f,
			2 / (top - bottom),
			0.0f,
			0.0f,

			0.0f,
			0.0f,
			-2.0f / (far - near),
			0.0f,

			-((right + left) / (right - left)),
			-((top + bottom) / (top - bottom)),
			-(far + near) / (far - near),
			1.0f
	);
	return t;
}

SMatrix4 FOrthographicLH(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar near, Scalar far)
{
	SMatrix4 t(
			2 / (right - left),
			0.0f,
			0.0f,
			0.0f,

			0.0f,
			2 / (top - bottom),
			0.0f,
			0.0f,

			0.0f,
			0.0f,
			1.0f / (far - near),
			0.0f,

			-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-(near / (far - near)),
			1.0f
	);
	return t;
}

SMatrix4 FLookAt(SVector3 fromPos, SVector3 toPos, SVector3 up)
{
	SVector3 f = FNormalize(toPos - fromPos);
	SVector3 s = FNormalize(FCross(f, up));
	SVector3 u = FCross(s, f);

	SMatrix4 t(
			s.x,
			u.x,
			-f.x,
			0.0f,

			s.y,
			u.y,
			-f.y,
			0.0f,

			s.z,
			u.z,
			-f.z,
			0.0f,

			-FDot(s, fromPos),
			-FDot(up, fromPos),
			FDot(f, fromPos),
			1.0f
	);
	return t;
}

Scalar FDeterminant(SMatrix4 m)
{
	return
			m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0] + m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0] +
			m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
			m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] - m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] + m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
			m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2] + m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2] +
			m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2] - m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] + m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
			m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] - m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] + m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] ;
}

SMatrix4 FInverse(SMatrix4 m)
{
	SMatrix4 t(
			m.m[1][2] *m.m[2][3] *m.m[3][1] -m.m[1][3] *m.m[2][2] *m.m[3][1] +m.m[1][3] *m.m[2][1] *m.m[3][2] -m.m[1][1] *m.m[2][3] *m.m[3][2] -m.m[1][2] *m.m[2][1] *m.m[3][3] +m.m[1][1] *m.m[2][2] *m.m[3][3],
			m.m[0][3] *m.m[2][2] *m.m[3][1] -m.m[0][2] *m.m[2][3] *m.m[3][1] -m.m[0][3] *m.m[2][1] *m.m[3][2] +m.m[0][1] *m.m[2][3] *m.m[3][2] +m.m[0][2] *m.m[2][1] *m.m[3][3] -m.m[0][1] *m.m[2][2] *m.m[3][3],
			m.m[0][2] *m.m[1][3] *m.m[3][1] -m.m[0][3] *m.m[1][2] *m.m[3][1] +m.m[0][3] *m.m[1][1] *m.m[3][2] -m.m[0][1] *m.m[1][3] *m.m[3][2] -m.m[0][2] *m.m[1][1] *m.m[3][3] +m.m[0][1] *m.m[1][2] *m.m[3][3],
			m.m[0][3] *m.m[1][2] *m.m[2][1] -m.m[0][2] *m.m[1][3] *m.m[2][1] -m.m[0][3] *m.m[1][1] *m.m[2][2] +m.m[0][1] *m.m[1][3] *m.m[2][2] +m.m[0][2] *m.m[1][1] *m.m[2][3] -m.m[0][1] *m.m[1][2] *m.m[2][3],
			m.m[1][3] *m.m[2][2] *m.m[3][0] -m.m[1][2] *m.m[2][3] *m.m[3][0] -m.m[1][3] *m.m[2][0] *m.m[3][2] +m.m[1][0] *m.m[2][3] *m.m[3][2] +m.m[1][2] *m.m[2][0] *m.m[3][3] -m.m[1][0] *m.m[2][2] *m.m[3][3],
			m.m[0][2] *m.m[2][3] *m.m[3][0] -m.m[0][3] *m.m[2][2] *m.m[3][0] +m.m[0][3] *m.m[2][0] *m.m[3][2] -m.m[0][0] *m.m[2][3] *m.m[3][2] -m.m[0][2] *m.m[2][0] *m.m[3][3] +m.m[0][0] *m.m[2][2] *m.m[3][3],
			m.m[0][3] *m.m[1][2] *m.m[3][0] -m.m[0][2] *m.m[1][3] *m.m[3][0] -m.m[0][3] *m.m[1][0] *m.m[3][2] +m.m[0][0] *m.m[1][3] *m.m[3][2] +m.m[0][2] *m.m[1][0] *m.m[3][3] -m.m[0][0] *m.m[1][2] *m.m[3][3],
			m.m[0][2] *m.m[1][3] *m.m[2][0] -m.m[0][3] *m.m[1][2] *m.m[2][0] +m.m[0][3] *m.m[1][0] *m.m[2][2] -m.m[0][0] *m.m[1][3] *m.m[2][2] -m.m[0][2] *m.m[1][0] *m.m[2][3] +m.m[0][0] *m.m[1][2] *m.m[2][3],
			m.m[1][1] *m.m[2][3] *m.m[3][0] -m.m[1][3] *m.m[2][1] *m.m[3][0] +m.m[1][3] *m.m[2][0] *m.m[3][1] -m.m[1][0] *m.m[2][3] *m.m[3][1] -m.m[1][1] *m.m[2][0] *m.m[3][3] +m.m[1][0] *m.m[2][1] *m.m[3][3],
			m.m[0][3] *m.m[2][1] *m.m[3][0] -m.m[0][1] *m.m[2][3] *m.m[3][0] -m.m[0][3] *m.m[2][0] *m.m[3][1] +m.m[0][0] *m.m[2][3] *m.m[3][1] +m.m[0][1] *m.m[2][0] *m.m[3][3] -m.m[0][0] *m.m[2][1] *m.m[3][3],
			m.m[0][1] *m.m[1][3] *m.m[3][0] -m.m[0][3] *m.m[1][1] *m.m[3][0] +m.m[0][3] *m.m[1][0] *m.m[3][1] -m.m[0][0] *m.m[1][3] *m.m[3][1] -m.m[0][1] *m.m[1][0] *m.m[3][3] +m.m[0][0] *m.m[1][1] *m.m[3][3],
			m.m[0][3] *m.m[1][1] *m.m[2][0] -m.m[0][1] *m.m[1][3] *m.m[2][0] -m.m[0][3] *m.m[1][0] *m.m[2][1] +m.m[0][0] *m.m[1][3] *m.m[2][1] +m.m[0][1] *m.m[1][0] *m.m[2][3] -m.m[0][0] *m.m[1][1] *m.m[2][3],
			m.m[1][2] *m.m[2][1] *m.m[3][0] -m.m[1][1] *m.m[2][2] *m.m[3][0] -m.m[1][2] *m.m[2][0] *m.m[3][1] +m.m[1][0] *m.m[2][2] *m.m[3][1] +m.m[1][1] *m.m[2][0] *m.m[3][2] -m.m[1][0] *m.m[2][1] *m.m[3][2],
			m.m[0][1] *m.m[2][2] *m.m[3][0] -m.m[0][2] *m.m[2][1] *m.m[3][0] +m.m[0][2] *m.m[2][0] *m.m[3][1] -m.m[0][0] *m.m[2][2] *m.m[3][1] -m.m[0][1] *m.m[2][0] *m.m[3][2] +m.m[0][0] *m.m[2][1] *m.m[3][2],
			m.m[0][2] *m.m[1][1] *m.m[3][0] -m.m[0][1] *m.m[1][2] *m.m[3][0] -m.m[0][2] *m.m[1][0] *m.m[3][1] +m.m[0][0] *m.m[1][2] *m.m[3][1] +m.m[0][1] *m.m[1][0] *m.m[3][2] -m.m[0][0] *m.m[1][1] *m.m[3][2],
			m.m[0][1] *m.m[1][2] *m.m[2][0] -m.m[0][2] *m.m[1][1] *m.m[2][0] +m.m[0][2] *m.m[1][0] *m.m[2][1] -m.m[0][0] *m.m[1][2] *m.m[2][1] -m.m[0][1] *m.m[1][0] *m.m[2][2] +m.m[0][0] *m.m[1][1] *m.m[2][2]
	);
	t *= FDeterminant(m);
	return t;
}

SMatrix4 FIdentity()
{
	return
			(
					SMatrix4{
							1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
					}
			);
}

VISRCEND
