//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_CUTILS_HPP
#define VICTORIAM_CUTILS_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/Memory/MUtils.hpp>
#include <Victoriam/Core/CCast.hpp>

VISRCBEG

template<class T> struct VIDECL SRemoveReference      { typedef T type; };
template<class T> struct VIDECL SRemoveReference<T&>  { typedef T type; };
template<class T> struct VIDECL SRemoveReference<T&&> { typedef T type; };

template<class T, auto N>
VIDECL constexpr auto FSize(T(&)[N]) { return N; }

template<class T>
VIDECL VIREQOUT constexpr T&& FMove(T&& v) noexcept { return static_cast<T&&>(v); }

template<class T>
VIDECL VIREQOUT inline T FMin(const T& a, const T& b) { return (a < b) ? a : b; }

template<class T>
VIDECL VIREQOUT inline T FMax(const T& a, const T& b) { return (b < a) ? a : b; }

VISRCEND

#endif //VICTORIAM_CUTILS_HPP
