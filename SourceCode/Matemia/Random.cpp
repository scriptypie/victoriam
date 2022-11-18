//
// Created by Вячеслав Кривенко on 13.11.2022.
//

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Matemia/Base/Random.hpp>

#include <random>

VISRCBEG

static std::random_device _random_device;
static std::mt19937_64 mt_engine(_random_device());

namespace Functions {

	Float32 FRandomF32(const Float32 &max, const Float32 &min) {
		std::uniform_real_distribution<Float32> dist(min, max);
		return dist(mt_engine);
	}

	Float64 FRandomF64(const Float64 &max, const Float64 &min) {
		std::uniform_real_distribution<Float64> dist(min, max);
		return dist(mt_engine);
	}

	Int8 FRandomI08(const Int8 &max, const Int8 &min) {
		std::uniform_int_distribution<Int8> dist(min, max);
		return dist(mt_engine);
	}

	UInt8 FRandomU08(const UInt8 &max, const UInt8 &min) {
		std::uniform_int_distribution<UInt8> dist(min, max);
		return dist(mt_engine);
	}

	Int16 FRandomI16(const Int16 &max, const Int16 &min) {
		std::uniform_int_distribution<Int16> dist(min, max);
		return dist(mt_engine);
	}

	UInt16 FRandomU16(const UInt16 &max, const UInt16 &min) {
		std::uniform_int_distribution<UInt16> dist(min, max);
		return dist(mt_engine);
	}

	Int32 FRandomI32(const Int32 &max, const Int32 &min) {
		std::uniform_int_distribution<Int32> dist(min, max);
		return dist(mt_engine);
	}

	UInt32 FRandomU32(const UInt32 &max, const UInt32 &min) {
		std::uniform_int_distribution<UInt32> dist(min, max);
		return dist(mt_engine);
	}

	Int64 FRandomI64(const Int64 &max, const Int64 &min) {
		std::uniform_int_distribution<Int64> dist(min, max);
		return dist(mt_engine);
	}

	UInt64 FRandomU64(const UInt64 &max, const UInt64 &min) {
		std::uniform_int_distribution<UInt64> dist(min, max);
		return dist(mt_engine);
	}

}

VISRCEND
