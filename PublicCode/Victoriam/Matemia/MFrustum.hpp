//
// Created by Вячеслав Кривенко on 17.11.2022.
//

#ifndef VICTORIAM_MFRUSTUM_HPP
#define VICTORIAM_MFRUSTUM_HPP

#include <Victoriam/Matemia/MPlan.hpp>

VISRCBEG

struct VIDECL SFrustum {
	SPlan top;
	SPlan bottom;
	SPlan right;
	SPlan left;
	SPlan far;
	SPlan near;
};

VISRCEND

#endif //VICTORIAM_MFRUSTUM_HPP
