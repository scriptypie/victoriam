//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#ifndef VICTORIAM_RANDOM_HPP
#define VICTORIAM_RANDOM_HPP

#include <Victoriam/Matemia/Base/Scalar.hpp>

VISRCBEG

namespace Functions
{

	VIDECL VIREQOUT Float32 FRandomF32(const Float32& max = (Float32)CONSTANT::INF, const Float32& min = (Float32)-CONSTANT::INF);
	VIDECL VIREQOUT Float64 FRandomF64(const Float64& max = (Float64)CONSTANT::INF, const Float64& min = (Float64)-CONSTANT::INF);
	VIDECL VIREQOUT Int8    FRandomI08(const Int8& max = (Int8)127, const Int8& min = (Int8)-128);
	VIDECL VIREQOUT UInt8   FRandomU08(const UInt8& max = (UInt8)255, const UInt8& min = (UInt8)0);
	VIDECL VIREQOUT Int16   FRandomI16(const Int16& max = (Int16)32767, const Int16& min = (Int16)-32768);
	VIDECL VIREQOUT UInt16  FRandomU16(const UInt16& max = (UInt16)65535, const UInt16& min = (UInt16)0);
	VIDECL VIREQOUT Int32   FRandomI32(const Int32& max = (Int32)2147483647, const Int32& min = (Int32)-2147483648);
	VIDECL VIREQOUT UInt32  FRandomU32(const UInt32& max = (UInt32)4294967295, const UInt32& min = (UInt32)0);
	VIDECL VIREQOUT Int64   FRandomI64(const Int64& max = (Int64)9223372036854775807, const Int64& min = (Int64)-9223372036854775807);
	VIDECL VIREQOUT UInt64  FRandomU64(const UInt64& max = (UInt64)18446744073709551615U, const UInt64& min = (UInt64)0);

}

template<class T>
class VIDECL CRandom {
public:
	VIDECL VIREQOUT inline static T Value() {}
	VIDECL VIREQOUT inline static T Range(const T& max) {}
	VIDECL VIREQOUT inline static T Range(const T& min, const T& max) {}
};

template<>
class VIDECL CRandom<Float32> {
public:
	VIDECL VIREQOUT inline static Float32 Value() { return Functions::FRandomF32(); }
	VIDECL VIREQOUT inline static Float32 Range(const Float32& max) { return Functions::FRandomF32(max); }
	VIDECL VIREQOUT inline static Float32 Range(const Float32& min, const Float32& max) { return Functions::FRandomF32(max, min); }
};

template<>
class VIDECL CRandom<Float64> {
public:
	VIDECL VIREQOUT inline static Float64 Value() { return Functions::FRandomF64(); }
	VIDECL VIREQOUT inline static Float64 Range(const Float64& max) { return Functions::FRandomF64(max); }
	VIDECL VIREQOUT inline static Float64 Range(const Float64& min, const Float64& max) { return Functions::FRandomF64(max, min); }
};

template<>
class VIDECL CRandom<Int8> {
public:
	VIDECL VIREQOUT inline static Int8 Value() { return Functions::FRandomI08(); }
	VIDECL VIREQOUT inline static Int8 Range(const Int8& max) { return Functions::FRandomI08(max); }
	VIDECL VIREQOUT inline static Int8 Range(const Int8& min, const Int8& max) { return Functions::FRandomI08(max, min); }
};

template<>
class VIDECL CRandom<UInt8> {
public:
	VIDECL VIREQOUT inline static UInt8 Value() { return Functions::FRandomU08(); }
	VIDECL VIREQOUT inline static UInt8 Range(const UInt8& max) { return Functions::FRandomU08(max); }
	VIDECL VIREQOUT inline static UInt8 Range(const UInt8& min, const UInt8& max) { return Functions::FRandomU08(max, min); }
};

template<>
class VIDECL CRandom<Int16> {
public:
	VIDECL VIREQOUT inline static Int16 Value() { return Functions::FRandomI16(); }
	VIDECL VIREQOUT inline static Int16 Range(const Int16& max) { return Functions::FRandomI16(max); }
	VIDECL VIREQOUT inline static Int16 Range(const Int16& min, const Int16& max) { return Functions::FRandomI16(max, min); }
};

template<>
class VIDECL CRandom<UInt16> {
public:
	VIDECL VIREQOUT inline static UInt16 Value() { return Functions::FRandomU16(); }
	VIDECL VIREQOUT inline static UInt16 Range(const UInt16& max) { return Functions::FRandomU16(max); }
	VIDECL VIREQOUT inline static UInt16 Range(const UInt16& min, const UInt16& max) { return Functions::FRandomU16(max, min); }
};

template<>
class VIDECL CRandom<Int32> {
public:
	VIDECL VIREQOUT inline static Int32 Value() { return Functions::FRandomI32(); }
	VIDECL VIREQOUT inline static Int32 Range(const Int32& max) { return Functions::FRandomI32(max); }
	VIDECL VIREQOUT inline static Int32 Range(const Int32& min, const Int32& max) { return Functions::FRandomI32(max, min); }
};

template<>
class VIDECL CRandom<UInt32> {
public:
	VIDECL VIREQOUT inline static UInt32 Value() { return Functions::FRandomU32(); }
	VIDECL VIREQOUT inline static UInt32 Range(const UInt32& max) { return Functions::FRandomU32(max); }
	VIDECL VIREQOUT inline static UInt32 Range(const UInt32& min, const UInt32& max) { return Functions::FRandomU32(max, min); }
};

template<>
class VIDECL CRandom<Int64> {
public:
	VIDECL VIREQOUT inline static Int64 Value() { return Functions::FRandomI64(); }
	VIDECL VIREQOUT inline static Int64 Range(const Int64& max) { return Functions::FRandomI64(max); }
	VIDECL VIREQOUT inline static Int64 Range(const Int64& min, const Int64& max) { return Functions::FRandomI64(max, min); }
};

template<>
class VIDECL CRandom<UInt64> {
public:
	VIDECL VIREQOUT inline static UInt64 Value() { return Functions::FRandomU64(); }
	VIDECL VIREQOUT inline static UInt64 Range(const UInt64& max) { return Functions::FRandomU64(max); }
	VIDECL VIREQOUT inline static UInt64 Range(const UInt64& min, const UInt64& max) { return Functions::FRandomU64(max, min); }
};

VISRCEND

#endif //VICTORIAM_RANDOM_HPP
