//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_CBASE_HPP
#define VICTORIAM_CBASE_HPP

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cstdint>
#include <tuple>
#include <thread>
#include <functional>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/CCast.hpp>
#include <Victoriam/Core/CFlags.hpp>
#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/Memory/MSmartPointers.hpp>
#include <Victoriam/Core/Memory/MStandardAllocator.hpp>

#include <Victoriam/Core/Containers/CArray.hpp>

VISRCBEG

VIDECL typedef char       Int8;
VIDECL typedef short      Int16;
VIDECL typedef int        Int32;
VIDECL typedef long long  Int64;

VIDECL typedef uint8_t  UInt8;
VIDECL typedef uint16_t UInt16;
VIDECL typedef uint32_t UInt32;
VIDECL typedef uint64_t UInt64;

VIDECL typedef UInt32 Signal;
VIDECL typedef UInt64 UID;

VIDECL typedef float_t  Float32;
VIDECL typedef double_t Float64;

VIDECL typedef bool     Bool;

VIDECL typedef const char* CString;
VIDECL typedef std::basic_string<char, std::char_traits<char>, StdAllocator<char> > String;
VIDECL typedef std::basic_stringstream<char, std::char_traits<char>, StdAllocator<char> > StringStream;

template<class T>
using List = std::vector<T, StdAllocator<T>>;

template<class...T>
using Tuple = std::tuple<T...>;

template<class...T, class...Args>
constexpr Tuple<T...> CreateTuple(Args&&...args)
{
	return std::make_tuple<T...>(std::forward<Args>(args)...);
}

template<class K, class V>
using UnorderedMap = std::unordered_map<K, V>;

template<class T>
using Function = std::function<T>;

VIDECL typedef List<char> BinaryData;

template<class T>
constexpr inline T min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

template<class T>
constexpr inline T max(const T& a, const T& b)
{
	return (b < a) ? a : b;
}

template<class T, auto N>
VIDECL constexpr auto StaticSize(T(&)[N]) { return N; }

VISRCEND

#endif //VICTORIAM_CBASE_HPP
