//
// Created by Вячеслав Кривенко on 01.12.2022.
//

#ifndef VICTORIAM_MUNIQUE_HPP
#define VICTORIAM_MUNIQUE_HPP

#include <Victoriam/Core/CUtils.hpp>
#include <Victoriam/Core/CNumerics.hpp>

VISRCBEG

template<class T>
using SUnique = std::unique_ptr<T>;

template<class T, class ...Args>
VIDECL inline constexpr SUnique<T> FMakeUnique(Args&&...args) {
	return SUnique<T> (new T(std::forward<Args>(args)...));
}

VISRCEND

#endif //VICTORIAM_MUNIQUE_HPP
