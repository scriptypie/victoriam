//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_CBASE_HPP
#define VICTORIAM_CBASE_HPP

#include <tuple>
#include <unordered_map>

#include <Victoriam/Core/Containers/CArray.hpp>
#include <Victoriam/Core/Containers/CConstant.hpp>
#include <Victoriam/Core/Containers/CSet.hpp>
#include <Victoriam/Core/Containers/CUniform.hpp>
#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/CFlags.hpp>
#include <Victoriam/Core/Memory/MSmartPointers.hpp>
#include <Victoriam/Core/CFunction.hpp>
#include <Victoriam/Matemia/MMath.hpp> // Matemia math library (property of github.com/scriptypie)

VISRCBEG

template<class...T>
using CTuple = std::tuple<T...>;

template<class...T, class...Args>
constexpr CTuple<T...> FCreateTuple(Args&&...args) {
	return std::make_tuple<T...>(std::forward<Args>(args)...);
}

template<class K, class V>
using CHashTable = std::unordered_map<K, V>;

VIDECL typedef CSet<char> CBinaryData;

VISRCEND

#endif //VICTORIAM_CBASE_HPP
