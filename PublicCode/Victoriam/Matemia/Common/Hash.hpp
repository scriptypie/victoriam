//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_HASH_HPP
#define VICTORIAM_HASH_HPP

#include <Victoriam/Matemia/MMatrix4.hpp>
#include <functional>

VISRCBEG

template<class HashType, class ST>
VIDECL constexpr HashType FHash(const ST& i) noexcept {
	union {
		ST hashable;
		HashType hashed;
	} packer;
	packer.hashed = CCast<HashType>(0);
	packer.hashable = i;
	return packer.hashed;
}

VISRCEND

namespace std {

	template<>
	struct hash<Vi::SVector2> {
		size_t operator()(const Vi::SVector2& v) const {
			size_t seed = 0;
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.x));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.y));
			return seed;
		}
	};

	template<>
	struct hash<Vi::SVector3> {
		size_t operator()(const Vi::SVector3& v) const {
			size_t seed = 0;
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.x));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.y));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.z));
			return seed;
		}
	};

	template<>
	struct hash<Vi::SVector4> {
		size_t operator()(const Vi::SVector4& v) const {
			size_t seed = 0;
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.x));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.y));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.z));
			Vi::FHashCombine(seed, Vi::FHash<std::size_t>(v.w));
			return seed;
		}
	};

	template<>
	struct hash<Vi::SMatrix4> {
		size_t operator()(const Vi::SMatrix4& m) const {
			size_t seed = 0;
			hash<Vi::SVector4> hasher;
			Vi::FHashCombine(seed, hasher(m[0]));
			Vi::FHashCombine(seed, hasher(m[1]));
			Vi::FHashCombine(seed, hasher(m[2]));
			Vi::FHashCombine(seed, hasher(m[3]));
			return seed;
		}
	};

}


#endif //VICTORIAM_HASH_HPP
