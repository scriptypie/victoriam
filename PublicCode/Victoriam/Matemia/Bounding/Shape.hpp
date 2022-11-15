//
// Created by Вячеслав Кривенко on 15.11.2022.
//

#ifndef VICTORIAM_SHAPE_HPP
#define VICTORIAM_SHAPE_HPP

#include <Victoriam/Matemia/Base/Base.hpp>
#include <Victoriam/Matemia/MPoint.hpp>

VISRCBEG

struct VIDECL SShape {
public:
	VIDECL VIREQOUT virtual Bool IsIntersects(const SPoint3D& point) const = 0;
	VIDECL VIREQOUT virtual Bool IsIntersects(const SSphere& sphere) const = 0;
	VIDECL VIREQOUT virtual Bool IsIntersects(const SAABB& box) const = 0;
};

VISRCEND

#endif //VICTORIAM_SHAPE_HPP
