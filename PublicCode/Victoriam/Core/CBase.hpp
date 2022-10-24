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
#include <functional>

#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/CCast.hpp>
#include <Victoriam/Core/CFlags.hpp>
#include <Victoriam/Core/CMacroDefinitions.hpp>
#include <Victoriam/Core/Memory/MSmartPointers.hpp>
#include <Victoriam/Core/Memory/MStandardAllocator.hpp>

VISRCBEG

VIDECL typedef char       Int8;
VIDECL typedef short      Int16;
VIDECL typedef int        Int32;
VIDECL typedef long long  Int64;

VIDECL typedef uint8_t  UInt8;
VIDECL typedef uint16_t UInt16;
VIDECL typedef uint32_t UInt32;
VIDECL typedef uint64_t UInt64;

VIDECL typedef float_t  Float32;
VIDECL typedef double_t Float64;

VIDECL typedef bool     Bool;

VIDECL typedef const char* CString;
VIDECL typedef std::basic_string<char, std::char_traits<char>, StdAllocator<char> > String;
VIDECL typedef std::basic_stringstream<char, std::char_traits<char>, StdAllocator<char> > StringStream;


template<class T>
using List = std::vector<T, StdAllocator<T>>;

template<class T, UInt32 N>
using Array = std::array<T, N>;

template<class T>
using Function = std::function<T>;

VIDECL typedef List<char> BinaryData;

template<class T, auto N>
VIDECL constexpr auto StaticSize(T(&)[N]) { return N; }

VISRCEND

#endif //VICTORIAM_CBASE_HPP
