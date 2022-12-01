//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_CBASE_HPP
#define VICTORIAM_CBASE_HPP

#include <vector>
#include <tuple>
#include <functional>
#include <unordered_map>

#include <Victoriam/Core/Containers/CArray.hpp>
#include <Victoriam/Core/Containers/CConstant.hpp>
#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/CFlags.hpp>
#include <Victoriam/Core/Memory/MSmartPointers.hpp>
#include <Victoriam/Matemia/MMath.hpp> // Matemia math library (property of github.com/scriptypie)

VISRCBEG

template<class T>
using CList = std::vector<T, StdAllocator<T>>;

template<class...T>
using CTuple = std::tuple<T...>;

template<class...T, class...Args>
constexpr CTuple<T...> FCreateTuple(Args&&...args)
{
	return std::make_tuple<T...>(std::forward<Args>(args)...);
}

template<class K, class V>
using CHashTable = std::unordered_map<K, V>;

template<class T>
using CFunction = std::function<T>;

VIDECL typedef CList<char> CBinaryData;

VISRCEND

#endif //VICTORIAM_CBASE_HPP
