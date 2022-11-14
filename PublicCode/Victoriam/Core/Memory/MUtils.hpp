//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_MUTILS_HPP
#define VICTORIAM_MUTILS_HPP

#include <Victoriam/Core/CCast.hpp>

#include <memory.h>

VISRCBEG

template<class T>
VIDECL inline void FMemcpy(T* dst, const T* src) {
	::memcpy(dst, src, sizeof(T));
}

template<class T>
VIDECL inline void FMemcpy(T* dst, const T* src, const size_t& size) {
	::memcpy(dst, src, size);
}

VISRCEND

#endif //VICTORIAM_MUTILS_HPP
