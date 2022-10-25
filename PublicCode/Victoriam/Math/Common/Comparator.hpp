//
// Created by Вячеслав Кривенко on 08.10.2022.
//

#ifndef VICTORIAM_COMPARATOR_HPP
#define VICTORIAM_COMPARATOR_HPP

#include <Victoriam/Math/Common/Scalar.hpp>

VISRCBEG

class CComparator
{
public:
	VIDECL static Bool Equal(const Scalar& a, const Scalar& b);
	VIDECL static Bool Greater(const Scalar& a, const Scalar& b);
	VIDECL static Bool Less(const Scalar& a, const Scalar& b);
};

VISRCEND

#endif //VICTORIAM_COMPARATOR_HPP
