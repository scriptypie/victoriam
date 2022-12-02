//
// Created by Вячеслав Кривенко on 01.12.2022.
//

#ifndef VICTORIAM_MUNIQUE_HPP
#define VICTORIAM_MUNIQUE_HPP

#include <Victoriam/Core/CUtils.hpp>
#include <Victoriam/Core/CNumerics.hpp>

VISRCBEG

template<class T>
struct VIDECL SUniqueDeleter;

template<class T>
struct VIDECL SUniqueTraits {
	using ValueType = T;
	using PointerType = T*;
	using ReferenceType = T&;
	using DeleterType = SUniqueDeleter<T>;
};

template<class T>
struct VIDECL SUniqueTraits<T[]> {
	using ValueType = T;
	using PointerType = T*;
	using ReferenceType = T&;
	using DeleterType = SUniqueDeleter<T[]>;
};

template<class T>
struct VIDECL SUniqueDeleter {
	using TraitsType = SUniqueTraits<T>;
	using PointerType = typename TraitsType::PointerType;

	VIDECL void operator()(PointerType p) {
		delete p;
		p = nullptr;
	}
};

template<class T>
struct VIDECL SUniqueDeleter<T[]> {
	using TraitsType = SUniqueTraits<T>;
	using PointerType = typename TraitsType::PointerType;

	VIDECL void operator()(PointerType p) {
		delete[] p;
		p = nullptr;
	}
};

template<class T>
class VIDECL CUnique {
public:
	using TraitsType = SUniqueTraits<T>;
	using PointerType = typename TraitsType::PointerType;
	using ReferenceType = typename TraitsType::ReferenceType;
	using DeleterType = typename TraitsType::DeleterType;
	template<class U>
	friend class CUnique;
private:
	PointerType m_Pointer = nullptr;
	DeleterType m_Deleter = {};
public:
	VIDECL CUnique() {}
	VIDECL CUnique(PointerType p) : m_Pointer(p) {}
	VIDECL CUnique(const CUnique&) = delete;
	VIDECL CUnique& operator=(const CUnique&) = delete;
	VIDECL CUnique(CUnique&& other) : m_Pointer(other.m_Pointer) { other.m_Pointer = nullptr; }
	VIDECL CUnique& operator=(CUnique&& other) {
		m_Deleter(m_Pointer);
		m_Pointer = other.m_Pointer;
		other.m_Pointer = nullptr;
		return *this;
	}
	template<class U>
	VIDECL CUnique(CUnique<U>&& other) noexcept : m_Pointer(other.m_Pointer) { other.m_Pointer = nullptr; }
	template<class U>
	VIDECL CUnique& operator=(CUnique<U>&& other) noexcept {
		m_Deleter(m_Pointer);
		m_Pointer = other.m_Pointer;
		other.m_Pointer = nullptr;
		return *this;
	}
	VIDECL ~CUnique() { m_Deleter(m_Pointer); }
	VIDECL VIREQOUT PointerType operator->() const {
		return m_Pointer;
	}
	VIDECL VIREQOUT ReferenceType operator*() const {
		return *m_Pointer;
	}
	VIDECL VIREQOUT PointerType Get() const {
		return m_Pointer;
	}
	VIDECL void Reset() {
		m_Deleter(m_Pointer);
	}
	VIDECL VIREQOUT Bool Empty() const {
		return !m_Pointer;
	}
	VIDECL VIREQOUT operator Bool() const {
		return m_Pointer;
	}
};

template<class T>
class VIDECL CUnique<T[]> {
public:
	using TraitsType = SUniqueTraits<T[]>;
	using PointerType = typename TraitsType::PointerType;
	using ReferenceType = typename TraitsType::ReferenceType;
	using DeleterType = typename TraitsType::DeleterType;
	template<class U>
	friend class CUnique;
private:
	PointerType m_Pointer = nullptr;
	DeleterType m_Deleter = {};
public:
	VIDECL CUnique() {}
	VIDECL explicit CUnique(PointerType p) : m_Pointer(p) {}
	VIDECL CUnique(const CUnique&) = delete;
	VIDECL CUnique& operator=(const CUnique&) = delete;
	VIDECL CUnique(CUnique&& other) noexcept : m_Pointer(other.m_Pointer) {}
	VIDECL CUnique& operator=(CUnique&& other) noexcept {
		m_Pointer = other.m_Pointer;
		return *this;
	}
	template<class U>
	VIDECL CUnique(CUnique<U>&& other) noexcept : m_Pointer(other.m_Pointer) {}
	template<class U>
	VIDECL CUnique& operator=(CUnique<U>&& other) noexcept {
		m_Pointer = other.m_Pointer;
		return *this;
	}
	VIDECL ~CUnique() { m_Deleter(m_Pointer); }
	VIDECL VIREQOUT PointerType operator->() const {
		return m_Pointer;
	}
	VIDECL VIREQOUT ReferenceType operator*() const {
		return *m_Pointer;
	}
	VIDECL VIREQOUT PointerType Get() const {
		return m_Pointer;
	}
	VIDECL void Reset() {
		m_Deleter(m_Pointer);
	}
	VIDECL VIREQOUT Bool Empty() const {
		return !m_Pointer;
	}
	VIDECL VIREQOUT operator Bool() const {
		return m_Pointer;
	}
	VIDECL ReferenceType At(const UInt64& pos) const {
		return m_Pointer[pos];
	}
	VIDECL ReferenceType operator[](const UInt64& pos) const {
		return At(pos);
	}
};

template<class T>
struct VIDECL SMakeUniqueIf {
	using SingleObjectType = CUnique<T>;
};

template<class T>
struct VIDECL SMakeUniqueIf<T[]> {
	using UnknownBoundObjects = CUnique<T[]>;
};

template<class T, auto N>
struct VIDECL SMakeUniqueIf<T[N]> {
	using KnownBoundObjects = void;
};

template<class T, class...Args>
VIDECL inline constexpr
typename SMakeUniqueIf<T>::SingleObjectType FMakeUnique(Args&&...args) {
	return CUnique<T>(new T(FForward<Args>(args)...));
}

template<class T>
VIDECL inline constexpr
typename SMakeUniqueIf<T>::UnknownBoundObjects FMakeUnique(const UInt64& count) {
	using ReType = typename SRemoveExtent<T>::Type;
	return CUnique<T>(new ReType[count]());
}

template<class T, class...Args>
VIDECL inline constexpr
typename SMakeUniqueIf<T>::KnownBoundObjects FMakeUnique(Args&&...) = delete;

VISRCEND

#endif //VICTORIAM_MUNIQUE_HPP
