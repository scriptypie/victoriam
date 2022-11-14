//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_CUTILS_HPP
#define VICTORIAM_CUTILS_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/CCast.hpp>

VISRCBEG

template<class T, auto N>
VIDECL constexpr auto FSize(T(&)[N]) { return N; }

template<class T>
VIDECL VIREQOUT constexpr T&& FMove(T&& v) noexcept { return static_cast<T&&>(v); }

VISRCEND

#endif //VICTORIAM_CUTILS_HPP
