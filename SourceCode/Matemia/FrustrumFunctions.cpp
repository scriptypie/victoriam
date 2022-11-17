//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#include <Victoriam/Matemia/Common/Functions.hpp>
#include <Victoriam/Matemia/MMatrix4.hpp>
#include <Victoriam/Matemia/MFrustrum.hpp>

VISRCBEG

SFrustrum FGetFrustrum(const SMatrix4& matrix, const Bool& normalize) {
	SFrustrum result;
	auto planes = result.planes;

	planes[0].a = matrix[0][3] + matrix[0][0];
	planes[0].b = matrix[1][3] + matrix[1][0];
	planes[0].c = matrix[2][3] + matrix[2][0];
	planes[0].d = matrix[3][3] + matrix[3][0];

	planes[1].a = matrix[0][3] - matrix[0][0];
	planes[1].b = matrix[1][3] - matrix[1][0];
	planes[1].c = matrix[2][3] - matrix[2][0];
	planes[1].d = matrix[3][3] - matrix[3][0];

	planes[2].a = matrix[0][3] - matrix[0][1];
	planes[2].b = matrix[1][3] - matrix[1][1];
	planes[2].c = matrix[2][3] - matrix[2][1];
	planes[2].d = matrix[3][3] - matrix[3][1];

	planes[3].a = matrix[0][3] + matrix[0][1];
	planes[3].b = matrix[1][3] + matrix[1][1];
	planes[3].c = matrix[2][3] + matrix[2][1];
	planes[3].d = matrix[3][3] + matrix[3][1];

	planes[4].a = matrix[0][3] + matrix[0][2];
	planes[4].b = matrix[1][3] + matrix[1][2];
	planes[4].c = matrix[2][3] + matrix[2][2];
	planes[4].d = matrix[3][3] + matrix[3][2];

	planes[5].a = matrix[0][3] - matrix[0][2];
	planes[5].b = matrix[1][3] - matrix[1][2];
	planes[5].c = matrix[2][3] - matrix[2][2];
	planes[5].d = matrix[3][3] - matrix[3][2];

	if (normalize)
		return FNormalize(result);
	return result;
}

SFrustrum FNormalize(const SFrustrum& frustrum) {
	SFrustrum result;
	result.planes[0] = FNormalize(frustrum.planes[0]);
	result.planes[1] = FNormalize(frustrum.planes[1]);
	result.planes[2] = FNormalize(frustrum.planes[2]);
	result.planes[3] = FNormalize(frustrum.planes[3]);
	result.planes[4] = FNormalize(frustrum.planes[4]);
	result.planes[5] = FNormalize(frustrum.planes[5]);
	return result;
}

VISRCEND
