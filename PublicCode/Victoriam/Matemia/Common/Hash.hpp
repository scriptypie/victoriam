//
// Created by Вячеслав Кривенко on 14.11.2022.
//

#ifndef VICTORIAM_HASH_HPP
#define VICTORIAM_HASH_HPP

#include <Victoriam/Matemia/MMatrix4.hpp>
#include <functional>

namespace std {

	template<>
	struct hash<Vi::SVector2> {
		size_t operator()(const Vi::SVector2& v) const {
			size_t seed = 0;
			hash<Vi::ScalarType> hasher;
			Vi::FHashCombine(seed, hasher(v.x));
			Vi::FHashCombine(seed, hasher(v.y));
			return seed;
		}
	};

	template<>
	struct hash<Vi::SVector3> {
		size_t operator()(const Vi::SVector3& v) const {
			size_t seed = 0;
			hash<Vi::ScalarType> hasher;
			Vi::FHashCombine(seed, hasher(v.x));
			Vi::FHashCombine(seed, hasher(v.y));
			Vi::FHashCombine(seed, hasher(v.z));
			return seed;
		}
	};

	template<>
	struct hash<Vi::SVector4> {
		size_t operator()(const Vi::SVector4& v) const {
			size_t seed = 0;
			hash<Vi::ScalarType> hasher;
			Vi::FHashCombine(seed, hasher(v.x));
			Vi::FHashCombine(seed, hasher(v.y));
			Vi::FHashCombine(seed, hasher(v.z));
			Vi::FHashCombine(seed, hasher(v.w));
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
