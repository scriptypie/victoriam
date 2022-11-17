//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MFRUSTRUM_HPP
#define VICTORIAM_MFRUSTRUM_HPP

#include <Victoriam/Matemia/MPlane.hpp>

VISRCBEG

struct VIDECL SFrustrum {
	union {
		ScalarArray<24> data = {};
		struct {
			SPlane planes[6];
		};
	};

	VIDECL inline ~SFrustrum() = default;
	VIDECL inline  SFrustrum() : data() {}
	VIDECL inline  SFrustrum(const SFrustrum& other) : data(other.data) {}
	VIDECL inline  SFrustrum(SFrustrum&& other) noexcept : data(FMove(other.data.data)) {}
	VIDECL inline  SFrustrum& operator=(const SFrustrum& other) { for (int i = 0; i < 6; i+=1) planes[i] = other.planes[i]; return *this; }
	VIDECL inline  SFrustrum& operator=(SFrustrum&& other) noexcept { for (int i = 0; i < 6; i+=1) planes[i] = FMove(other.planes[i]); return *this; }

};

VISRCEND

#endif //VICTORIAM_MFRUSTRUM_HPP
